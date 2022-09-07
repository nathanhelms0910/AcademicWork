#include "filesys.h"
#include <iostream>

void test4() {
  int fd;
  int fd2;
  string buffer;
  Filesystem* sys = new Filesystem("test.img",4194304);
  sys->format();
  sys->create("test1.txt");
  sys->rename("test1.txt", "dymacek.txt");
  fd = sys->open("dymacek.txt", 0, 0);
  sys->write(fd, "OS is pain", 10);
  sys->copy("dymacek.txt", "marmorstein.txt");
  fd2 = sys->open("marmorstein.txt", 0, 0);
  sys->close(fd);
  sys->read(fd2, buffer, 10);
  sys->close(fd2);
  sys->mv("dymacek.txt", "blaheta.txt");
  cout << "Buffer: " << buffer << endl;
  cout << sys->list() << endl;
  delete sys;
}

void test3() {
  Filesystem* sys = new Filesystem("test.img",4194304);
  sys->format();
  sys->create("test1.txt");
  int fd = sys->open("test1.txt", 0, 0);
  sys->write(fd, "Hello", 5);
  sys->close(fd);
  sys->copy("test1.txt", "copy.txt");
  cout << sys->list() << endl;
  delete sys;
}

void test2() {
  int fd;
  string str = "string test";
  string buffer;
  Filesystem* sys = new Filesystem("test.img",4194304);
  sys->format();
  sys->create("test1.txt");
  cout << sys->list() << endl;
  sys->rename("test1.txt", "renamed1.txt");
  fd = sys->open("renamed1.txt", 1, 0);
  sys->write(fd, str, 11);
  sys->close(fd);
  fd = sys->open("renamed1.txt", 0, 1);
  sys->read(fd, buffer, 11);

  cout << "Read Buffer: " << buffer << endl;
  cout << sys->list() << endl;
  delete sys;
}


void test1() {
  Filesystem* sys = new Filesystem("test.img",4194304);
  sys->format();
  sys->create("test1.txt");
  sys->create("test2.txt");
  sys->create("test3.txt");
  cout << sys->list() << endl;

  sys->rm("test2.txt");
  cout << sys->list() << endl;
  delete sys;
}

int main(){
  //test1();
  //test2();
  //test3();
  test4();
  return 0;
}
