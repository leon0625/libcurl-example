
/* 
 * 连接复用测试，一次连接，多次请求数据
 */
#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
 
int main(void)
{
  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be an https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080");
    /* Now specify the POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"name\":\"aaaa\",\"age\":18}}");

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    struct curl_slist *hs=NULL;
    hs = curl_slist_append(hs, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
 
    // 第一次请求数据
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    sleep(10);
    // 重启http服务器，检查第二次是否会重连还是怎么样。
    // 经测试，会重启建立tcp连接。

    // 第二次请求数据
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"name\":\"aaaa\",\"age\":22}}");
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */
    curl_easy_cleanup(curl);
    curl_slist_free_all(hs);
  }
  curl_global_cleanup();
  return 0;
}