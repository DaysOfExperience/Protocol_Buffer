all: read write

write:write.cc contacts.pb.cc
	g++ -o $@ $^ -std=c++11 -lprotobuf

read:read.cc contacts.pb.cc
	g++ -o $@ $^ -std=c++11 -lprotobuf

.PHONY:clean
clean:
	rm -f read write