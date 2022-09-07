#include "filesys.h"
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

struct DirectoryEntries
{
  char filename[16];
  int index = -1;
  int size = -1;
};

vector<int> fds;
vector<FileHandle*> openFiles;
int fileDescIterator = 0;

void Filesystem::format()
{
  for(int i = 0; i < m_disk_size; ++i)
  {
	m_disk[i] = '*';
  }
}

bool Filesystem::create(const string name)
{
  int newFileIndex = 0;
  int index = 0;
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  if(name.length() > 15)
  {
	return false;
  }
  for(int i = 0; i < m_disk_size / 4000; ++i)
  {
	
	if(strcmp(entries[i].filename, name.c_str()) == 0)
	{
	  return false;
	}
	if(entries[i].filename[0] == '*')
	{
  	  index = i;	  
	  newFileIndex = (4000*sizeof(DirectoryEntries))+(i*1024);
	  if(newFileIndex > m_disk_size) {
		return false;
	  }
	  break;
	}

  }
  strcpy(entries[index].filename, name.c_str());
  entries[index].index = newFileIndex;
  entries[index].size = 0;
  return true;
}

string Filesystem::list() const
{
  stringstream strstm;
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  for(int i = 0; i < 4000; ++i)
  {
	if(entries[i].filename[0] == '*')
	{
	  continue;
	}
	strstm << entries[i].filename;
	for(int j = strlen(entries[i].filename); j < 16; ++j)
	{
	  strstm << " ";
	}
	strstm << "	" << entries[i].index;
	strstm << "	" << entries[i].size << endl;
  }
  return strstm.str();
}
  /*Loop through directory entries and print formatted listings. Pad white space in each with spaces if needed
	*/

bool Filesystem::rm(const string name)
{
  string zeroOut = "***************";
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  for(int i = 0; i < 4000; ++i)
  {
	if(strcmp(entries[i].filename, name.c_str()) == 0)
	{
	  strcpy(entries[i].filename, zeroOut.c_str());
	  entries[i].size = -1;
	  entries[i].index = -1;
	  return true;
	}
  }
  return false;

}

bool Filesystem::rename(const string old_name, const string new_name)
{
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  for(int i = 0; i < 4000; ++i)
  {
	if(strcmp(entries[i].filename, old_name.c_str()) == 0)
	{
	  for(int j = 0; j < m_disk_size / 4000; ++j)
	  {
		if(strcmp(entries[j].filename, new_name.c_str()) == 0)
		{
		  return false;
		}
	  }
	  strcpy(entries[i].filename, new_name.c_str());
	  return true;
	}
  }
  return false;
}

//GLITTER FUNCTION

bool Filesystem::mv(const string old_name, const string new_name)
{
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  for(int i = 0; i < 4000; ++i)
  {
	if(strcmp(entries[i].filename, old_name.c_str()) == 0)
	{
	  for(int j = 0; j < 4000; ++j)
	  {
		if(strcmp(entries[j].filename, new_name.c_str()) == 0)
		{
		  rm(entries[j].filename);
		}
	  }
	  rename(old_name, new_name);
	  return true;
	}
  }
  return false;
}


bool Filesystem::copy(const string old_name, const string new_name)
{
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  for(int i = 0; i < 4000; ++i)
  {
	if(strcmp(entries[i].filename, old_name.c_str()) == 0)
	{
	  create(new_name);
	  for(int j = 0; j < 4000; ++j)
	  {
		if(strcmp(entries[j].filename, new_name.c_str()) == 0)
		{
		  memcpy(&m_disk[entries[j].index], &m_disk[entries[i].index], 1024);
		  entries[j].size = entries[i].size;
		  return true;
		}
	  }
	  break;

	}
  }
  return false;
}

//GLITTER: read only/write only on open
int Filesystem::open(const string name, int r, int w)
{
  int newFile;
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  for(int i = 0; i < 4000; ++i)
  {
	if(strcmp(entries[i].filename, name.c_str()) == 0)
	{
	  FileHandle* file = new FileHandle;
	  file->pos = entries[i].index;
	  file->size = entries[i].size;
	  file->offset = 0;
	  if(r == 1)
	  {
		file->ro = true;
	  }
	  else
	  {
		file->ro = false;
	  }
	  if(w == 1)
	  {
		file->wo = true;
	  }
	  else
	  {
		file->wo = false;
	  }
	  if(fileDescIterator <= 256)
	  {
		newFile = fileDescIterator;
		fds.push_back(fileDescIterator);
		openFiles.push_back(file);
		++fileDescIterator;
		break;
	  }
	  else
	  {
		return -1;
	  }
	}
  }
  return newFile;
}

bool Filesystem::close(const int fd) const
{
  if(fd < 0)
  {
	return false;
  }
  for(int i = 0; i < fds.size(); ++i)
  {
	if(fds[i] == fd)
	{
	  fds.erase(fds.begin()+i);
	  openFiles.erase(openFiles.begin()+i);
	  --fileDescIterator;
	  break;
	}
  }
  return true;
}

bool Filesystem::read(const int fd, string &buf, const unsigned int size) const
{
  int fdesc;
  if(fd < 0 || fd > 255)
  {
	return false;
  }
  for(int i = 0; i < fds.size(); ++i)
  {
	if(fds[i] == fd)
	{
	  fdesc = i;
	  break;
	}
  }
  if(openFiles[fdesc]->wo)
  {
	cout << "File is write only" << endl;
	return false;
  }
  int pos = openFiles[fdesc]->pos + openFiles[fdesc]->offset;
  if(read_string(pos, buf, size))
  {
	openFiles[fdesc]->offset = openFiles[fdesc]->offset + size;
	return true;
  }
  else
  {
	return false;
  }
}

bool Filesystem::write(const int fd, const string str, const unsigned int size)
{
  DirectoryEntries* entries;
  entries = (DirectoryEntries *)m_disk;
  int fdesc;
  if(fd < 0 || fd > 255)
  {
	return false;
  }
  for(int i = 0; i < fds.size(); ++i)
  {
	if(fds[i] == fd)
	{
	  fdesc = i;
	  break;
	}
  }
  if(openFiles[fdesc]->ro)
  {
	cout << "File is read only" << endl;
	return false;
  }
  int pos;
  for(int i = 0; i < size; ++i)
  {
    pos = openFiles[fdesc]->pos + openFiles[fdesc]->offset;
	m_disk[pos] = str[i];
	++openFiles[fdesc]->offset;
  }
  for(int i = 0; i < 4000; ++i)
  {
	if(entries[i].index == openFiles[fdesc]->pos)
	{
	  entries[i].size = entries[i].size + size;
	  break;
	}
  }
}
