/*
 *  cReddit_main.h
 *  cReddit
 *
 *  Created by Eric Gallager on 7/13/13.
 *
 */

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include <stdio.h>

/*
 * Prototypes
 *
 */

void buildScreen(char **text, int selected, int size);
void showSubreddit(char *subreddit);

/* "main" does not normally need a prototype here */
