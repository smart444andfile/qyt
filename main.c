#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_video () {
	char search[256];
	char command[512];
	char buffer[4096];
	char title[5][256];
	char id[5][64];
	printf("search : ");
	fgets(search, sizeof(search), stdin);
	search[strcspn(search, "\n")] = 0;
	snprintf(command, sizeof(command), "yt-dlp 'ytsearch5:%s' --get-title --get-id" , search);
	int i = 0;
	FILE *fp = popen(command, "r");

	while (fgets(buffer, sizeof(buffer), fp) != NULL){
		buffer[strcspn(buffer, "\n")] = 0;
		if (i % 2 == 0) {
			strcpy(title[i/2], buffer);
		} else {
			strcpy(id[i/2], buffer);
		} i++;
	}
	for (int j = 0; j < 5; j++){
		printf("%d. %s\n", j+1 , title[j]);
	}
	printf("what video you want to watch : ");
	int pick;
	scanf("%d", &pick);
	getchar();

	char mpv_cmd[2048];
	snprintf(mpv_cmd, sizeof(mpv_cmd), "mpv 'https://youtube.com/watch?v=%s' --ytdl", id[pick-1]);

	system(mpv_cmd);

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
		char purl[2048];
		char mpv_cmd_url[2048];
		printf("paste url : ");
		scanf("%s", purl);
		snprintf(mpv_cmd_url, sizeof(mpv_cmd_url), "mpv '%s' --ytdl",purl);
		system(mpv_cmd_url);
	}
}
