/*
 * main.c
 *
 */

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jsmn.h"
#include "reddit.h"
#include "cReddit_main.h"
#include <curl/curl.h>
#include <ncurses.h>
#include <form.h>

#define SIZEOFELEM(x)  (sizeof(x) / sizeof(x[0]))


void buildScreen(char **text, int selected, int size)
{
    clear();
    start_color();
    init_pair((short)1, (short)COLOR_RED, (short)COLOR_YELLOW);
    int i = 0;
    for(i = 0; i != size; ++i)
    {
        if(i == selected)
            attron(COLOR_PAIR(1));
        printw("%s\n",text[i]);
        attroff(COLOR_PAIR(1));
    }
    refresh();
}

void showSubreddit(char *subreddit)
{
    struct post threads[25]; // Our array with reddit threads
    int *postCount;
    postCount = malloc(sizeof(int));
    redditGetSubreddit(subreddit,"hot",threads,postCount);
    // Just some ncurses testing
    int i;
    int displayCount = 25;
    if (*postCount < 25) {
        displayCount=*postCount;
    }
    printw("%i\n", displayCount);
    char *text[displayCount]; // Text buffer for each line
    for(i = 0; i != displayCount; ++i)
    {
        if(threads[i].id == 0)
            continue;
        char buffer[2048]; // Let us make a big-ass text buffer so we have enough space
        strcpy(buffer,threads[i].id);
        strcat(buffer," (");
        strcat(buffer,threads[i].votes);
        strcat(buffer,") ");
        strcat(buffer,threads[i].title);
        strcat(buffer," - ");
        strcat(buffer,threads[i].author);
        text[i] = (char*)malloc(strlen(buffer)); // Now let us make a small buffer that fits exactly!
        strcpy(text[i],buffer); // And copy our data into it!
        printw("%s\n",buffer);
        refresh();
    }

    int selected = 0; // Let us select the first post!
    buildScreen(text,selected,displayCount); // And print it!
    int c;
    struct comments cList[500];
    while((c = wgetch(stdscr))) // just using extra parentheses to silence the warning for now...
    {
        if(c == 'q') // Let us make a break key, so that I do not have to close the tab like last time :S
            break; // YEA FUCK YOU "WHILE"!
        switch(c)
        {
            case KEY_UP:
                if(selected != 0)
                    selected--;
                break;

            case KEY_DOWN:
                if(selected != 24)
                    selected++;
                break;

            case '\n':
                refresh();
                int *commentCount;
                commentCount = malloc(sizeof(int));
                redditGetThread(threads[selected].id,cList,commentCount);
                int cdisplayCount = 25;
                if (*commentCount < 25) {
                    cdisplayCount=*postCount;
                }
                // Basically a copy of the code above (use a macro instead?)
                int u;
                char *ctext[cdisplayCount]; // Text buffer for each line
                for(u = 0; u != cdisplayCount; ++u)
                {
#if 0
                    printw("starting"); // ifdefed out because...?
#endif /* 0 */
                    if(cList[u].id == 0 || cList[u].text == NULL || cList[u].id == NULL || cList[u].author == NULL)
                        continue;
                    char cbuffer[2048];
                    strcpy(cbuffer,cList[u].id);
                    strcat(cbuffer," ");
                    strcat(cbuffer,cList[u].author);
                    // Votes will have to be implemented with up votes minus
                    // downvotes (currently ifdefed out because...?)
#if 0
                    strcat(cbuffer," (");
                    strcat(cbuffer,cList[u].votes);
                    strcat(cbuffer,")");
#endif /* 0 */
                    strcat(cbuffer," - ");
                    strcat(cbuffer,cList[u].text);
                    ctext[u] = (char*)malloc(strlen(cbuffer)); // Now let us make a small buffer that fits exactly!
                    strcpy(ctext[u],cbuffer); // And copy our data into it!
                    printw("%s\n",cbuffer);
                    refresh();
                }
		wgetch(stdscr);
		for(u = 1; u != cdisplayCount; ++u)
                {
		    free(ctext[u]);
		}
		free(commentCount);
        }
        buildScreen(text,selected,displayCount); // Print the updates!!
    }
    for(i = 1; i != displayCount; ++i)
    {
        free(text[i]);
    }
    free(postCount);
}

int main(int argc, char *argv[])
{
    printf("\n Message for security and/or debugging: \n This program's path is %s and it is running with %i argument(s). \n", argv[0], argc); // Statement for debugging
    initscr();
    raw(); // We want character for character input
    keypad(stdscr, (bool)1); // Enable extra keys like arrowkeys
    noecho();
    curl_global_init((long)CURL_GLOBAL_ALL);

    // In case the user does not specify an argument
    if (!argv[1]) {
        curl_global_cleanup(); // Do not forget to clean up!!! My whole terminal bugged because you forgot this :-)
        endwin();
        printf("Please supply a subreddit to go to e.g. /r/coding\n"); // Added a newline
        exit(0);
    }

    showSubreddit(argv[1]);
    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();
    endwin();
    return 0;
}
