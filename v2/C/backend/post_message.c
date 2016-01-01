#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#include "CGI_functions.h"
#include "SQL_functions.h"

int main(int argc, char ** argv){
    cgi datCGI;
    init_CGI(&datCGI);
	person check_person;
	init_person(&check_person);

	get_CGI_data(&datCGI);
	if(datCGI.http_cookies == NULL)print_exit_failure("Cookies müssen aktiv und gesetzt sein!");

	//Anhand der SID und der Email wird geprüft ob der aktuelle Benutzer angemeldet ist.
	char * s_sid=NULL;
    extract_COOKIE_data(&datCGI, "SID", &s_sid);
    extract_COOKIE_data(&datCGI, "EMAIL", &check_person.email);
    check_person.sid=atoi(s_sid);


    if(verify_sid(&check_person)){
		//httpHeader(TEXT);
		get_person_by_sid(&check_person);
		message mes;
		init_message(&mes);

		mes.creator_id=check_person.id;

		extract_POST_data(&datCGI, "meldung", &mes.message);
		extract_POST_data(&datCGI, "titel", &mes.title);

		fprintf(stderr, "\n\nPOST_DATA: '%s'\n\n", datCGI.POST_data);

		time_t now=time(NULL);
		mes.created=localtime(&now);


		//mes.message=convert_to_html(mes.message);

		fprintf(stderr, "\n\nTitel: '%s',\nNachricht: '%s'\n\n\nend", mes.title, mes.message);

		//TODO: diese Programm soll auch für Kursbezogene Meldungen funktionieren
		asprintf(&mes.courses, "all");

		insert_message(&mes);
		char * redirectString=NULL;
		asprintf(&redirectString, "https://%s/cgi-bin/all_messages.cgi", datCGI.http_host);
		httpRedirect(redirectString);


    }else{
    	char * redirectString=NULL;
		asprintf(&redirectString, "https://%s/index.html", datCGI.http_host);
		httpRedirect(redirectString);
    }

    exit(0);
}
