# 线程安全  
libcurl自称是线程安全，但看网上还是说有踩坑的。  
  
**要点如下：**  
* 设置CURLOPT_NOSIGNAL为1, `easy_setopt(curl, CURLOPT_NOSIGNAL, (long)1);`  
* 程序一开始就调用curl_global_init(CURL_GLOBAL_DEFAULT);  

# 连接复用
libcurl 默认就会使用连接复用选项，如果不想使用，可以使用如下两个选项来配置为1。
```c
CURL *curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 0L);

// 发送第一个请求
curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, 0L);
curl_easy_perform(curl);

// 发送第二个请求
curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, 0L);
curl_easy_perform(curl);

curl_easy_cleanup(curl);
```

[CURLOPT_FORBID_REUSE](https://curl.se/libcurl/c/CURLOPT_FORBID_REUSE.html)默认为0，开启连接复用。  
[CURLOPT_FRESH_CONNECT](https://curl.se/libcurl/c/CURLOPT_FRESH_CONNECT.html)默认为0，开启连接复用。  
  
* 经测试，如果第一个curl_easy_perform请求完数据后，http连接断开，第二个curl_easy_perform会自动重新建立tcp连接  

## 问题
（1）一个curl句柄post get不同网站数据，出现段错误，原因不详
解决：使用curl前调用curl_easy_reset(curl);后不再出现。
该reset只是reset选项，并不会清空连接，dns缓存,cookie等信息


# 常用代码  
  
* 显示详细打印  
`curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);`  

* 设置接收数据的回调  
`CURLOPT_WRITEFUNCTION`  
回调原型为`size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);`  
size固定为1，返回值如果不等于nmemb，那么会终止传输，curl会返回CURLE_WRITE_ERROR  
可通过`CURLOPT_WRITEDATA`设置userdata  

