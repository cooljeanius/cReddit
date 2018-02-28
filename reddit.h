/*
 * reddit.h
 *
 */

#ifndef __REDDIT_H_
#define __REDDIT_H_

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jsmn.h"
#include "cReddit_main.h"
#include <curl/curl.h>

#define REDDIT_URL_BASE_LENGTH 21

/*
 * structs
 */

struct MemoryStruct {
  	char *memory;
  	size_t size;
};

struct post {
	char * title;
	char * votes;
	char * id;
	char * author;
	char * subreddit;
};

struct comments {
	char * text;
	char * id;
	char * author;
	char * votes;
};

/*
 * Prototypes
 */

char* prepend(char *pre, char *str);
void redditGetThread(char * postid, struct comments * commentList, int * commentCount);
void redditGetSubreddit(char * sub, char * sorting, struct post * postList, int * postCount);
char *ask_for_subreddit(void);
void showSubreddit(char *subreddit);
void cleanup(void);
int startsWith(char *pre, char *str);

#endif /* !__REDDIT_H__ */

/* EOF */
