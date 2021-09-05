#include <curl/curl.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdint>

#include "network.h"

// Cannot include raylib.h here, or globals.h because it includes raylib.h
// These conflict with windows.h, which is included by curl/curl.h
extern uint32_t score;
extern char username[17];
extern "C"
{
	const char *TextFormat(const char *text, ...);
}

void PostScores(void)
{
	// Code modified from https://curl.se/libcurl/c/http-post.html
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, PostEndpoint);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "GeometrySlash");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, TextFormat("username=%s&score=%d", username, score));

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if(res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
	}
}


// Code modified from https://curl.se/libcurl/c/getinmemory.html

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if(!ptr) {
		/* out of memory! */
		fprintf(stderr, "not enough memory (realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

char* GetScores(void)
{
	CURL *curl_handle;
	CURLcode res;

	struct MemoryStruct chunk;

	chunk.memory = (char*)malloc(1);	/* will be grown as needed by the realloc above */
	chunk.size = 0;		/* no data at this point */


	/* init the curl session */
	curl_handle = curl_easy_init();

	/* specify URL to get */
	curl_easy_setopt(curl_handle, CURLOPT_URL, GetEndpoint);

	/* send all data to this function	*/
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers don't like requests that are made without a user-agent
		 field, so we provide one */
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "GeometrySlash");

	/* get it! */
	res = curl_easy_perform(curl_handle);

	/* check for errors */
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(res));
	}
	else {
		/*
		 * Now, our chunk.memory points to a memory block that is chunk.size
		 * bytes big and contains the remote file.
		 *
		 * Do something nice with it!
		 */

		printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	return chunk.memory;
}

