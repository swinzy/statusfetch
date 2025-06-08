#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "os.h"

#ifdef _WIN32
    #define EMOJI   ":window:"
#elif __linux__
    #define EMOJI   ":penguin:"
#elif __APPLE__
    #define EMOJI   ":apple:"
#else
    #define EMOJI   ":computer:"
#endif

#define GITHUB_API_ENDPOINT     "https://api.github.com/graphql"
#define USER_AGENT              "User-Agent: statusfetch/1.0"

void set_status(const char* token, const char* name)
{
    CURL *curl;
    CURLcode result;

    // Populate query according to OS
    char query[256];
    snprintf(query, sizeof(query), "{\"query\": \"mutation { changeUserStatus(input: {message: \\\"%s\\\", emoji: \\\"%s\\\"}) { status { message emoji } } }\"}", name, EMOJI);

    curl = curl_easy_init();
    if (!curl)
    {
        fprintf(stderr, "Cannot init curl\n");
    }
    else
    {
        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", token);

        headers = curl_slist_append(headers, auth_header);
        headers = curl_slist_append(headers, USER_AGENT);
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, GITHUB_API_ENDPOINT);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query);

        result = curl_easy_perform(curl);

        if (result != CURLE_OK)
            fprintf(stderr, "curl request failed: %s\n", curl_easy_strerror(result));

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

int main()
{
    // Detect OS
    const char *os = get_os_name();
    
    // Cannot detect os
    if (!os) {
        return 1;
    }

    // Get Github Token
    const char *token = getenv("GITHUB_TOKEN");
    if (!token)
    {
        fprintf(stderr, "No token defined in environment\n");
        return 1;
    }

    set_status(token, os);

    return 0;
}
