/*
 *  metaws.c
 *
 *  This program extends i3 workspaces by allowing for 'meta' workspaces.
 *  Think of a meta-workspace as a container that holds the 10 regular
 *  workspaces provided by i3.
 *
 *  When i3 starts, metaws will use meta-workspace 0.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

const char META_NAME[] = "meta_ws";
char cfgfile[PATH_MAX];

#define MAX_WORKSPACE_NAME_LEN 64

char *progname;
char meta_ws[MAX_WORKSPACE_NAME_LEN];
char targ_ws[MAX_WORKSPACE_NAME_LEN];
char foc_ws[MAX_WORKSPACE_NAME_LEN];

extern void usage();
extern int readMeta();
extern int writeMeta();
extern int isEmpty(char *p);
extern int args(int argc, char **argv);

int
main(int argc, char* argv[]){
    int i;
    char *cp;
    char cmd[128 + MAX_WORKSPACE_NAME_LEN * 2];
    progname = ((cp = strchr(argv[0], '/')) == NULL) ? argv[0] : ++cp;


    for(i=0; i < MAX_WORKSPACE_NAME_LEN; i++)
        meta_ws[i] = targ_ws[i] = foc_ws[i] = '\0';

    if(args(--argc, ++argv) <= 0)
        usage();

    strcat(strncpy(cfgfile, getenv("HOME"), sizeof(cfgfile)), "/.config/i3/.meta_ws");
    FILE *p_metafile = fopen(cfgfile, "r");
    if(p_metafile == NULL){
        p_metafile = fopen(cfgfile, "w");
        fprintf(p_metafile, "0");
    }
    fclose(p_metafile);

    if(!isEmpty(meta_ws) && !writeMeta()){
        fprintf(stderr, "%s: unable to write to '%s'\n", progname, cfgfile);
        return 1;
    }else if(isEmpty(meta_ws)){
        readMeta();
    }

    if(!isEmpty(foc_ws)){
        strcpy(cmd, "i3-msg \"workspace ");
        strcat(cmd, meta_ws);
        strcat(cmd, foc_ws);
        strcat(cmd, ";\" >/dev/null 2>&1");
        system(cmd);
    }

    if(!isEmpty(targ_ws)){
        strcpy(cmd, "i3-msg \"move container to workspace ");
        strcat(cmd, meta_ws);
        strcat(cmd, targ_ws);
        strcat(cmd, ";\" >/dev/null 2>&1");
        system(cmd);
    }
	return 0;
}

int
args(int argc, char **argv){
    int i;
    if (argc == 0 || argv == NULL)
        return -1;
    for(i = 0; i < argc && argv[i] != NULL; i++){
        if(strcmp(argv[i], "-M") == 0)
            strncpy(meta_ws, argv[++i], sizeof(meta_ws));
        else if(strcmp(argv[i], "-w") == 0)
            strncpy(foc_ws, argv[++i], sizeof(foc_ws));
        else if(strcmp(argv[i], "-m") == 0)
            strncpy(targ_ws, argv[++i], sizeof(targ_ws));
        else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            usage();
        else{
            fprintf(stderr, "%s: could not process argument '%s'\n\n",
                    progname, argv[i]);
            usage();
        }
    }

    return i;
}

int
readMeta(){
    int i;
    char c;
    FILE *fp;
    char buf[MAX_WORKSPACE_NAME_LEN];

    if((fp = fopen(cfgfile, "r")) == NULL)
        return 0;

    for(i = 0; i < MAX_WORKSPACE_NAME_LEN; i++)
        buf[i] = ((c = fgetc(fp)) == EOF || c == '\n' || c == '\r') ? '\0' : c;

    strncpy(meta_ws, buf, sizeof(meta_ws));
    fclose(fp);
    return 1;
}

int
writeMeta(){
    FILE *fp;
    if((fp = fopen(cfgfile, "w")) == NULL)
        return 0;
    fprintf(fp, "%s", meta_ws);
    fclose(fp);
    return 1;
}

void
usage(){
    fprintf(stderr, "Usage: %s [-M meta_ws] [-w foc_ws] ", progname);
    fprintf(stderr, "[-m targ_ws]\n");
    fprintf(stderr, "Manages collections (meta-workspaces) of your active i3 ");
    fprintf(stderr, "workspaces.\n\n");
    fprintf(stderr, "%4s,%-15s  %-56s\n", "-h", " --help",
            "Displays this message and exits");
    fprintf(stderr, "%4s %-15s  %-56s\n", "-M", "<meta_ws>",
            "Sets the currently displayed meta-workspace to <meta_ws>");
    fprintf(stderr, "%4s %-15s  %-56s\n", "-m", "<targ_ws>",
            "Moves the currently focused window to <targ_ws>");
    fprintf(stderr, "%4s %-15s  %-56s\n", "-w", "<foc_ws>",
            "Changes the focused workspace to <foc_ws>");
    fprintf(stderr, "\n");
    exit(1);
}

int
isEmpty(char *p){
    return p[0] == '\0';
}
