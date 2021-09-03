#include <curl/curl.h>

#include "network.h"
#include "globals.h"

void PostScores(void)
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, PostEndpoint);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, TextFormat("username=%s&score=%d", username, score));

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if(res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
	}
}
