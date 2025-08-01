#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recorder.h"
#include "replayer.h"
#include "analyzer.h"
#include <sys/stat.h>

#define DEFAULT_SESSION_FILE "data/session.json"

#include <stdio.h>

#ifndef REWINDTTY_VERSION
#define REWINDTTY_VERSION "dev"
#endif

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <record|replay|analyze> [session_file]\n", argv[0]);
        return 1;
    }

    if (argc > 1)
    {
        if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
        {
            printf("rewindtty version %s\n", REWINDTTY_VERSION);
            return 0;
        }
    }

    const char *session_file = DEFAULT_SESSION_FILE;

    if (strcmp(argv[1], "record") == 0)
    {
        if (argc >= 3)
        {
            session_file = argv[2];
        }
        else
        {
            mkdir("data", 0755);
        }
        start_recording(session_file);
    }
    else if (strcmp(argv[1], "replay") == 0)
    {
        replay_session_from_file(session_file, 1.0);
    }
    else if (strcmp(argv[1], "analyze") == 0)
    {
        analyze_session(session_file);
    }
    else
    {
        fprintf(stderr, "Unknown command '%s'. Use 'record', 'replay', or 'analyze'\n", argv[1]);
        return 1;
    }

    return 0;
}
