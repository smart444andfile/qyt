#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_video () {
	char search[256];
	char command[512];
	char buffer[4096];
	char title[5][256];
	char id[5][64];
	memset(title, 0, sizeof(title));
	memset(id, 0, sizeof(id));

	printf("search : ");
	fgets(search, sizeof(search), stdin);
	search[strcspn(search, "\n")] = 0;
	snprintf(command, sizeof(command), "yt-dlp 'ytsearch5:%s' --get-title --get-id" , search);
	int i = 0;
	FILE *fp = popen(command, "r");

	if (fp == NULL) {
		printf("yt-dlp not installed yet bro");
		return 1;
	}
	while (fgets(buffer, sizeof(buffer), fp) != NULL){
		buffer[strcspn(buffer, "\n")] = 0;
		if (i % 2 == 0 && i/2 < 5) {
			strncpy(title[i/2], buffer, sizeof(title[i/2]) - 1);
		} else {
			strncpy(id[i/2], buffer, sizeof(id[i/2]) - 1);
		} i++;
	}
	pclose(fp);

	int real_results = (i / 2);
	for (int j = 0; j < real_results; j++){
		printf("%d. %s\n", j+1 , title[j]);
	}

	if (real_results == 0) return 1;

	printf("what video you want to watch : ");
	int pick;
	if (scanf("%d", &pick) != 1){
		printf("INVALID INPUT BRO!!!");
		while(getchar() != '\n');
		return 1;
	}
	if (pick < 1 || pick > real_results) {
		printf("PICK BETWEEN 1 and %d YOU IDIOT\n", real_results);
	}

	char mpv_cmd[2048];
	snprintf(mpv_cmd, sizeof(mpv_cmd), "mpv 'https://youtube.com/watch?v=%s' --ytdl", id[pick-1]);

	system(mpv_cmd);

	return 0;
}

int url_pasre (){
	char purl[2048];
	char mpv_cmd_url[2048];
	printf("paste url : ");
	fgets(purl, sizeof(purl), stdin);
	snprintf(mpv_cmd_url , sizeof(mpv_cmd_url), "mpv '%s' --ytdl" , purl);
	system(mpv_cmd_url);

	return 0;
}
int main (){
	int sel;
	printf("do you want to search or paste url (1/2) : ");
	scanf("%d", &sel);
	getchar();
	if (sel == 1){
		search_video();	
	} else if (sel == 2){
		url_pasre();
	} else {
		printf("pick only 1 or 2 bro am not that dumb \n");
	}
}
