#include <curl/curl.h>
#include <string>
#include <fstream>
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

std::string ServerURL = "http://localhost:3000";

std::string GetEndpoint;
std::string PostEndpoint;

void CurlInit(void)
{
	// Must wrap this function, cannot include raylib.h and curl/curl.h in the same file
	// Because curl/curl.h includes windows.h
	curl_global_init(CURL_GLOBAL_ALL);
}

void CurlCleanup(void)
{
	// Same reason as above
	curl_global_cleanup();
}

void ReadURL(void)
{
	std::ifstream urlfile("url.txt");
	// Read URL from url.txt if it's present
	// Should be in the form http://whatever.xyz:3000
	// if it fails to open the file, the URL will just default to localhost:3000
	if (urlfile.is_open())
	{
		ServerURL.clear();
		std::getline(urlfile, ServerURL);
		urlfile.close();
	}
	GetEndpoint = ServerURL + GetSuffix;
	PostEndpoint = ServerURL + PostSuffix;
}


void PostScores(void)
{
	// Code modified from https://curl.se/libcurl/c/http-post.html
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, PostEndpoint.c_str());
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
	size_t realsize = size*nmemb;
	((std::string*)userp)->append((char*)contents, realsize);
	return realsize;
}

std::string& GetScores(int page)
{
	CURL *curl_handle;
	CURLcode res;

	static std::string response;

	response.clear();

	/* init the curl session */
	curl_handle = curl_easy_init();

	/* specify URL to get */
	curl_easy_setopt(curl_handle, CURLOPT_URL, TextFormat(GetEndpoint.c_str(), page*10));

	/* send all data to this function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* pass the string to the callback function */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

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

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);

	return response;
}

