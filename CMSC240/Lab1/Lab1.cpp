#include "duedateresource.h"
#include "duedateresource.moc"
#include "settings.h"
#include "settingsadaptor.h"
#include <QtDBus/QDBusConnection>
#include "configdialog.h"
#include <KWindowSystem>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDomDocument>
#include <QDomNode>
#include <QDomNodeList>
#include <KCal/Incidence>
#include <KCal/Event>
#include <KIO/NetAccess>
#include <akonadi/changerecorder.h>
#include <akonadi/itemfetchscope.h>
#include <boost/shared_ptr.hpp>

using namespace Akonadi;
using namespace KCal;
typedef boost::shared_ptr<KCal::Incidence>IncidencePtr; DueDateResource::DueDateResource( const QString &id ) : ResourceBase( id ) {
  new SettingsAdaptor( Settings::self() );
  QDBusConnection::sessionBus().registerObject( QLatin1String( "/Settings" ), Settings::self(), QDBusConnection::ExportAdaptors );
  changeRecorder()->itemFetchScope().fetchFullPayload(); // TODO: you can put any resource specific initialization code here.  netManager = 0; editManager = 0;
}

DueDateResource::~DueDateResource() {
  if (netManager)
    delete netManager;
}

void DueDateResource::retrieveCollections() { // TODO: this method is called when Akonadi wants to have all the // collections your resource provides.
					      // Be sure to set the remote ID and the content MIME types
  Collection c;
  c.setParent( Collection::root() );
  c.setRemoteId( "akonadi_duedate_resource_" + Settings::self()->course() + "_" + Settings::self()->semester());
  c.setName( Settings::self()->course() + "_" + Settings::self()->semester());
  c.setContentMimeTypes( QStringList() << "application/x-vnd.akonadi.calendar.event" );
  //c.setRights( Collection::ReadOnly );
  Collection::List list; list << c;
  collectionsRetrieved( list );
}

void DueDateResource::retrieveItems( const Akonadi::Collection &collection ) {
  Q_UNUSED(collection); // TODO: this method is called when Akonadi wants to know about all the
 			 // items in the given collection. You can but don't have to provide all the
			 // data for each item, remote ID and MIME type are enough at this stage.
		       	 // Depending on how your resource accesses the data, there are several
			 // different ways to tell Akonadi when you are done.
  const QString course = Settings::self()->course();
  const QString semester = Settings::self()->semester();
  if (!netManager){
    netManager = new QNetworkAccessManager(this);
    connect(netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
  }
netManager->get(QNetworkRequest(QUrl(Settings::self()->url() + "?course=" + course + "&username=webuser&semester=" + semester)));

}

void DueDateResource::uploadFinished(QNetworkReply* reply){
  if (reply->error() == QNetworkReply::NoError) {
    QString response; response = reply->readAll();
    if (response.indexOf("Success") >= 0){
      mPendingItem.setRemoteId(response.replace("Success: ", ""));
      changeCommitted(mPendingItem);
    }
    else{
      emit error("Error Uploading Due Date: Server issued fail response.\n"); cancelTask();
    }
  }
  else{
    emit error(QString("Error Uploading Due Date: %1.\n").arg(reply->errorString())); cancelTask();
  }
}

void DueDateResource::replyFinished(QNetworkReply* reply){
  QString course;
  QString semester;
  course = Settings::self()->course();
  semester = Settings::self()->semester();
  Item::List items;
  QDomDocument doc;
  QByteArray content = reply->readAll();
  QString content_str(content); //Todo: Add error handling
  QString error_message;
  int error_line;
  int error_col;
  if (!doc.setContent(content, false, &error_message, &error_line, &error_col)){ //An error has occurred in line error_line.
     emit error(QString("%1 in line %2 (%3).  Content: %4\n").arg(error_message).arg(error_line).arg(error_col).arg(content_str));
     cancelTask();
     return;
  }
  QDomNodeList projectNodes = doc.elementsByTagName("project");
  for (unsigned int i=0;i<projectNodes.length();i++){
    QDomNode node = projectNodes.item(i);
    if (node.isNull()){
      emit error("Node was null");
      continue;
    }
    QDomNode dateNode = node.firstChild().firstChild();
    if (dateNode.isNull()){
      emit error("Date was null");
      continue;
    }
    QString dateText = dateNode.nodeValue();
    QDomNode textNode = node.firstChild().nextSibling().firstChild();
    if (textNode.isNull()){
      emit error("Text node was null");
      continue;
    }
    QString nameText = textNode.nodeValue();
    QDomNode fileNode = node.firstChild().nextSibling().nextSibling().nextSibling().firstChild();
    QDomNode fileNameNode = node.firstChild().nextSibling().nextSibling().firstChild();
    QString fileData;
    QString fileName;
    if (!fileNode.isNull()){
      fileData = fileNode.nodeValue();
      if (!fileNameNode.isNull())
       	fileName = fileNameNode.nodeValue();
      else fileName = QString("Untitled Document");
    }
    KDateTime start = KDateTime::fromString(dateText, "%Y-%m-%d %H:%M:%S");
    if (!start.isValid()){
      emit error(QString("Date was invalid: %1.\n").arg(dateText));
      cancelTask();
      return;
    }
    KCal::Event incidence;
    incidence.setUid(course + semester + dateText);
    incidence.setDtStart(start);
    incidence.setDtEnd(start.addSecs(3000));
    incidence.setStatus(KCal::Event::StatusConfirmed);
    incidence.setSummary(nameText);
    incidence.setDescription(course);
    if (!fileData.isNull()){
      KCal::Attachment* attach = new KCal::Attachment(fileData.toAscii().data());
      attach->setLabel(fileName);
      incidence.addAttachment(attach);
    }
    IncidencePtr evptr(incidence.clone());
    Item item("application/x-vnd.akonadi.calendar.event");
    item.setRemoteId(course + "_" + semester + "_" + nameText + "_" + dateText);
    item.setPayload<IncidencePtr>(evptr);
    incidence.setReadOnly(Settings::self()->readOnly());
    items << item;
  }
  delete reply;
  itemsRetrieved(items);
}

bool DueDateResource::retrieveItem( const Akonadi::Item &item, const QSet<QByteArray> &parts ) {
  Q_UNUSED( item );
  Q_UNUSED( parts ); // TODO: this method is called when Akonadi wants more data for a given item.
		     // You can only provide the parts that have been requested but you are allowed
		     // to provide all in one go
  return true;
}

void DueDateResource::aboutToQuit() {  // TODO: any cleanup you need to do while there is still an active
 				       // event loop. The resource will terminate after this method returns
}

void DueDateResource::configure( WId windowId ) { // TODO: this method is usually called when a new resource is being
 						  // added to the Akonadi setup. You can do any kind of user interaction here,
						  // e.g. showing dialogs. 
						  // The given window ID is usually useful to get the correct
						  // "on top of parent" behavior if the running window manager applies any kind
						  // of focus stealing prevention technique
 ConfigDialog dialog;
 if (windowId)
   KWindowSystem::setMainWindow(&dialog, windowId);
   dialog.exec();
   synchronize();
}

void DueDateResource::itemAdded( const Akonadi::Item &item, const Akonadi::Collection &collection ) { // TODO: this method is called when somebody else, e.g. a client application,
 												      // has created an item in a collection managed by your resource. 
												      // NOTE: There is an equivalent method for collections, but it isn't part
												      // of this template code to keep it simple
 Q_UNUSED( collection );
 QUrl myUrl(Settings::self()->url());
 IncidencePtr evptr;
 boost::shared_ptr<KCal::Event> event;
 if (item.hasPayload<IncidencePtr>()){
   evptr = item.payload<IncidencePtr>();
   event = boost::dynamic_pointer_cast<KCal::Event, KCal::Incidence>(evptr);
   myUrl.addQueryItem("add", "1");
   myUrl.addQueryItem("course", Settings::self()->course());
   myUrl.addQueryItem("semester", Settings::self()->semester());
   myUrl.addQueryItem("date", event->dtStart().toString());
   myUrl.addQueryItem("username", "webuser");
   myUrl.addQueryItem("name", event->summary());
   if (event->attachments().size() > 0){
     KCal::Attachment* at = event->attachments()[0];
     myUrl.addQueryItem("fname", at->label());
     if (at->isUri()){
       QString tmpFileName;
       KIO::NetAccess::download(QUrl(at->uri()), tmpFileName, new QWidget());
       QFile tmpFile(tmpFileName);
       tmpFile.open(QIODevice::ReadOnly);
       QByteArray data = tmpFile.readAll();
       myUrl.addQueryItem("file", data.toBase64());
       tmpFile.close();
     }
     else{
       myUrl.addQueryItem("file", at->data());
     }
   }
   if (!editManager){
     editManager = new QNetworkAccessManager(this);
     connect(editManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadFinished(QNetworkReply*)));
   }
   QNetworkRequest* req = new QNetworkRequest(Settings::self()->url());
   mPendingItem = item; editManager->post(*req, myUrl.encodedQuery());
 }
 else{
   emit error("No payload of type IncidencePtr.\n"); cancelTask();
 }
}

void DueDateResource::itemChanged( const Akonadi::Item &item, const QSet<QByteArray> &parts ) {
  Q_UNUSED( item ); Q_UNUSED( parts ); // TODO: this method is called when somebody else, e.g. a client application,
 				       // has changed an item managed by your resource. 
				       // NOTE: There is an equivalent method for collections, but it isn't part
				       // of this template code to keep it simple
  QUrl myUrl(Settings::self()->url());
  IncidencePtr evptr; boost::shared_ptr<KCal::Event> event;
  if (item.hasPayload<IncidencePtr>()){
    evptr = item.payload<IncidencePtr>();
    event = boost::dynamic_pointer_cast<KCal::Event, KCal::Incidence>(evptr);
    QString rid = item.remoteId();
    myUrl.addQueryItem("id", rid);
    myUrl.addQueryItem("edit", "1");
    myUrl.addQueryItem("course", Settings::self()->course());
    myUrl.addQueryItem("semester", Settings::self()->semester());
    myUrl.addQueryItem("date", event->dtStart().toString());
    myUrl.addQueryItem("username", "webuser");
    myUrl.addQueryItem("name", event->summary());
    if (event->attachments().size() > 0){
      KCal::Attachment* at = event->attachments()[0];
      myUrl.addQueryItem("fname", at->label());
      if (at->isUri()){
       	QString tmpFileName;
       	KIO::NetAccess::download(QUrl(at->uri()), tmpFileName, new QWidget());
       	QFile tmpFile(tmpFileName);
       	tmpFile.open(QIODevice::ReadOnly);
       	QByteArray data = tmpFile.readAll();
       	myUrl.addQueryItem("file", data.toBase64());
       	tmpFile.close();
      }
      else{
       	myUrl.addQueryItem("file", at->data());
      }
    }
    if (!editManager){
      editManager = new QNetworkAccessManager(this);
      connect(editManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadFinished(QNetworkReply*)));
    }
    QNetworkRequest* req = new QNetworkRequest(Settings::self()->url());
    mPendingItem = item;
    editManager->post(*req, myUrl.encodedQuery());
  }
  else{
    emit error("No payload of type IncidencePtr.\n");
    cancelTask();
  }
}

void DueDateResource::itemRemoved( const Akonadi::Item &item ) {
  Q_UNUSED( item ); // TODO: this method is called when somebody else, e.g. a client application,
 		    // has deleted an item managed by your resource.
		    // NOTE: There is an equivalent method for collections, but it isn't part
		    // of this template code to keep it simple
  QUrl myUrl(Settings::self()->url());
  QString rid = item.remoteId();
  myUrl.addQueryItem("id", rid);
  myUrl.addQueryItem("course", Settings::self()->course());
  myUrl.addQueryItem("semester", Settings::self()->semester());
  myUrl.addQueryItem("username", "webuser");
  myUrl.addQueryItem("remove", "1");
  if (!editManager){
    editManager = new QNetworkAccessManager(this);
    connect(editManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadFinished(QNetworkReply*)));
  }
  QNetworkRequest* req = new QNetworkRequest(Settings::self()->url());
  mPendingItem = item;
  editManager->post(*req, myUrl.encodedQuery());
}

AKONADI_RESOURCE_MAIN( DueDateResource )
