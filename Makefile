CC=g++
CFLAGS= -Wall -I/usr/include/mysqlcoppconn -L/usr/lib/mysqlcppconn
LFLAGS= -lmysqlcppconn

all: app
	./app

app: clean 
	$(CC) $(CFLAGS) main.cpp connect.cpp auth.cpp teacher.cpp student.cpp clearS.cpp totAvMarks.cpp -o app $(LFLAGS)

clean:
	rm -f app