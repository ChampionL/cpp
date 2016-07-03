#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include "rapidjson/error/en.h"



int main(){
	int fd = open("/home/laicb/c++/json/conf/config.json",O_RDWR);
	if(fd==-1){
		printf("%s",strerror(errno));
		return -1;
	}
	char buf[1024]={0};
	if(read(fd,buf,1024)<0){
		printf("%s",strerror(errno));
		return -1;
	}
	//rapidjson::Document d;
	//d.Parse(buf);
	//char buf2[1024]="{\"hello\":1}\0"; 
	//const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	//printf("%s\n",json);
	rapidjson::Document d;
	//Parse在解析之前首先调用isobject进行判断，isobject进行判断，其进行判断很复杂，会检测后面调用
	if (d.Parse(buf).HasParseError()) {
		fprintf(stderr, "\nError(offset %u): %s\n", 
				(unsigned)d.GetErrorOffset(),
				rapidjson::GetParseError_En(d.GetParseError()));
		// ...
	}
	//rapidjson::StringStream sbuf(buf);
	//	d.ParseStream(sbuf);
	//printf("%s %u\n",result.Code(),result.Offset());
	//if (!result) {
	//	std::cerr << "JSON parse error: %s (%u)", result.GetParseError_En(result.Code()), result.Offset();
	//}
	//d.Parse(buf);

	//rapidjson::Value & s = d["hello"];
	//printf("%d\n",s.GetInt());
	std::string hello;
	if(d.HasMember("hello") && d["hello"].IsString()){
	      hello = d["hello"].GetString();
	}
	bool t,f;
	if(d.HasMember("t") && d["t"].IsBool()){
	     t = d["t"].GetBool();
	}
	
	if(d.HasMember("f") && d["f"].IsBool()){
	     f = d["f"].GetBool();
	}
	bool IsNull;
	if(d.HasMember("t") && d["t"].IsNull() ){
	   IsNull = d["t"].IsNull();
	}	
	int num;	
	if(d.HasMember("i") && d["i"].IsInt()){
	     num = d["i"].GetInt();
	}
	double pi;	
	if(d.HasMember("pi") && d["pi"].IsNumber()){
	     pi = d["pi"].GetDouble();
	}
	printf("%s\n",hello.c_str());
	printf("%d\n",t);
	printf("%d\n",f);
	printf("%d\n",IsNull);	
	printf("%d\n",num);
	printf("%f\n",pi);
	
	//处理数组
	if(d.HasMember("a") && d["a"].IsArray()){
		for(rapidjson::SizeType i=0;i<d["a"].Size();i++){
		   printf("%d\n",d["a"][i].GetInt());
		}
	}
	return 0;
}
