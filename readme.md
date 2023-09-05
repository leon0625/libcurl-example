# 线程安全  
libcurl自称是线程安全，但看网上还是说有踩坑的。  
  
**要点如下：**  
* 设置CURLOPT_NOSIGNAL为1, `easy_setopt(curl, CURLOPT_NOSIGNAL, (long)1);`  
* 程序一开始就调用curl_global_init(CURL_GLOBAL_DEFAULT);  
  
# 常用代码  
  
* 显示详细打印  
`curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);`  

* 设置接收数据的回调  
`CURLOPT_WRITEFUNCTION`

