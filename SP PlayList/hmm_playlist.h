
void read_playlist_songs()
{
	FILE *fp_ind;
	char completePathInd[200];
	char completePathSystemCommand[200];
	char word_per_line[num_of_char_per_line];

	int tot_lang=totWords-lang_index_begin;

	for(int lg=lang_index_begin;lg<totWords;lg++)
	{
		for(int w=0; w<max_Songs ;w++)
			{
				free(playlist_songs_arr[lg][w]);
			}
	}

	for(int lg=lang_index_begin;lg<totWords;lg++)
	{
		sprintf(completePathInd, "SONGS/%s/songs.txt",HMM_WORDS[lg]); 
		sprintf(completePathSystemCommand, "dir SONGS\\%s /B | findstr /v /i \"\\.txt$\" > %s",HMM_WORDS[lg], completePathInd);  
		//printf("\n File Name is: %s\n", completePathInd);
		//printf("\n File Name is: %s\n", completePathSystemCommand);
		system(completePathSystemCommand);

		fp_ind = fopen(completePathInd, "r");				
			if(fp_ind == NULL){ 
				perror("\nError: ");
				printf("\n Song List File Name is: %s\n", completePathInd);
				getch();
				return;
			}

		int sis=0;
		while(fgets(word_per_line, num_of_char_per_line, fp_ind)!=NULL){
			char* s;
			s=(char*)malloc(sizeof(*s)*(num_of_char_per_line+1)); 
			word_per_line[strlen(word_per_line)-1] = '\0';
			strcpy(s,word_per_line);
			playlist_songs_arr[lg][sis]=s;
			sis++;
		}

			//printf("\nSongs:: %s\n",HMM_WORDS[lg]);
			//for(int w=0; w<max_Songs ;w++)
			//{
			//	printf("%d. [%d][%s]\n",w,lg,playlist_songs_arr[lg][w]);
			//}

	fflush(fp_ind); fclose(fp_ind);
	}//for lg
	
}

/**************************************************************************************************
	Test Live Utterance of the Language
**************************************************************************************************/
int live_testing_playlist(unsigned int model_type_to_use, int lang_index)
{
	
	/**************** Observation Sequence Generation ****************/
	live_sequence_generation(LIVETESTING);
	/**************** Read Observation Sequence ****************/
	readObsSeqOfLiveRecording(LIVETESTING);

	/**************** Testing ****************/
	int NumOfLiveUtterance=1;

	long double cur_alpha_probability=0;
	long double max_probability=0;
	int word_index=-1;
	
	int tot=0;

	if(lang_index==0)
	{
		tot = lang_index_begin;
	}
	else if(lang_index==lang_index_begin)
	{
		tot = totWords;
	}

	for(int u=0; u<NumOfLiveUtterance; u++){
		printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~> Live PlayList Lang Utterance: %s_obs_seq_O[%d] \n", liveRecordingFileName, 1);
			
		max_probability=0;
		cur_alpha_probability=0;
		word_index=-1;
		for(int w=lang_index; w<tot; w++){
			readLambdaABPi(w, model_type_to_use);
			cur_alpha_probability=P1_Forward_Procedure(O[u],u);

					printf("O[%d]:W[%s]::  Alpha P = %g\n", u+1, HMM_WORDS[w], cur_alpha_probability); 	 
					fprintf(fp_console, "O[%d]:W[%s]::  Alpha P = %g\n", u+1, HMM_WORDS[w], cur_alpha_probability); 	 

			if(cur_alpha_probability > max_probability){
				max_probability = cur_alpha_probability;
				word_index=w;
			}
		}//for each w word
		if(word_index==-1)
		{
			printf("\n -----------------> Word Recognized: %s\n", "NOT RECOGNIZED");
			fprintf(fp_console, "\n -----------------> Word Recognized: %s\n", "NOT RECOGNIZED" );
			return lang_index;
		}
		else
		{
			printf("\n -----------------> Word Recognized: %s\n", HMM_WORDS[word_index]);
			fprintf(fp_console, "\n -----------------> Word Recognized: %s\n", HMM_WORDS[word_index]);
		}
	}// for each u utterance	
	//fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 

	return word_index;
}


//void Play_Songs(int lang_ind, int song_index)
//{
//	char path_folder[300];
//	printf("\n\n\n--------------------------------------------------------------------------\n\n\n ");
//	sprintf(path_folder, "\"SONGS\\%s\\%s\"", HMM_WORDS[lang_ind], playlist_songs_arr[lang_ind][song_index]);  //file_name
//		printf("\n PLAYING SONG: ");
//		printf("%s\n", path_folder);
//
//	system(path_folder); // open default music player to play the song
//
//	printf("\n\n\n--------------------------------------------------------------------------\n\n\n ");
//}


void PlayList_Songs(int _ind)
{
	
	char choice;	
	char path_folder[300];
	unsigned int model_type_use = OutputFolderModel;

	do{ // Lang Loop
		char ch;
		printf("\n\n\n");
		system("pause");
		system("cls");
		printf("\n\n ------- -------~~ SPEAK INDEX ~~------- -------");

		printf("\n \"%s\" SONGS::\n", strupr(HMM_WORDS[_ind]));

		for(int w=0; w<max_Songs ;w++)
		{
			printf("\n %d. [%s]\n", w, playlist_songs_arr[_ind][w]);
		}

		//sprintf(path_folder, "start explorer .\\SONGS\\%s",HMM_WORDS[_ind]);  //file_name
		//	system(path_folder);

		char correct_voice;
		//scanf("%c%*c", &ch);
		printf("\n <-------->");
		printf("\n Duration 3 sec: \n"); 
		timestamp = time(NULL);
		
		/**************** Creating necessary file Path for data. ****************/
		sprintf(liveRecordingFileName, "playlist_%s_livetest_%ld",HMM_WORDS[_ind], timestamp);  //file_name
		sprintf(liveRecordingCommand, "%s 3 %s %s%s.txt", recording_module_exe_path, liveRecordingWAV, input_live_voice_folder, liveRecordingFileName);  
		//printf("\n path: %s\n",liveRecordingCommand );
		do 	//record loop
		{
			printf("\n Enter To Record.");
			getch();
			printf("\n");
			/**************** Execute the Live Recording Module ****************/
			system(liveRecordingCommand);		//execute the command
			//USAGE : "Recording_Module.exe" <duration_in_seconds> <output_mono_wav_file_path> <output_text_file_path>
						
			printf("\n Playing Your Sound: "); 
			PlaySound(TEXT(liveRecordingWAV), NULL, SND_SYNC );
			//system(wavform_WAV); // create waveform of file
			printf("\n\n Is Word Correctly Spoken ?" 
				"\n\t	opt = 4: will repeat the recording process. "
				"\n\t	opt = 5: will proceed and do the testing. "
				"\n\n  --Choice :  ");
			//scanf("%c%*c",&correct_voice);
			scanf("%c",&correct_voice);

			while ((getchar()) != '\n');

		}while(correct_voice!='5');	//record loop	

		fprintf(fp_console, "\n ----------------------- ----------------------- > LIVE TESTING : %s < ----------------------- \n",liveRecordingFileName );
			
		/**************** Live Testing ****************/
		int _index = live_testing_playlist(model_type_use, 0);
		/**************** Play Songs ****************/
		//Play_Songs(_ind, _index);

		printf("\n\n\n--------------------------------------------------------------------------\n\n\n ");
		sprintf(path_folder, "\"SONGS\\%s\\%s\"", HMM_WORDS[_ind], playlist_songs_arr[_ind][_index]);  //file_name
			printf("\n PLAYING SONG: ");
			printf("%s\n", path_folder);

		system(path_folder); // open default music player to play the song

		printf("\n\n\n--------------------------------------------------------------------------\n\n\n ");
		printf("\n\n p. Try Another Song.");
		printf("\n n. Return To PlayList		\n\n  --Choice : ");
		scanf("%c%*c", &ch);
		choice=ch;
	} while (choice != 'n'); // Song Loop
}


/**************************************************************************************************
	PlayList Menu
**************************************************************************************************/
int PlayListMenu(){
	system("cls");
	
	read_playlist_songs();

	char model_type_string[20] = "new_model";
	char choice;		// choice exercised.

	do{ // Lang Loop
		char ch, correct_voice;
		int word=0, uttr_seq=1;
		unsigned int model_type_use = OutputFolderModel;
		printf("\n\n\n");
		system("pause");
		system("cls");

		/**************** Display Languages. ****************/
		printf("\n\n ------- -------~~ SPEAK LANGUAGE ~~------- -------");

		for(int lg=0;lg<(totWords-lang_index_begin);lg++)
		{
			printf("\n %d. SPEAK \"%s\" for %s Songs", lg+1, strupr(HMM_WORDS[lang_index_begin+lg]), HMM_WORDS[lang_index_begin+lg]);
		}
		//scanf("%c%*c", &ch);
		printf("\n <-------->");
		printf("\n Duration 3 sec: \n"); 
		timestamp = time(NULL);
	
		/**************** Creating necessary file Path for data. ****************/
		sprintf(liveRecordingFileName, "playlist_livetest_%ld", timestamp);  //file_name
		sprintf(liveRecordingCommand, "%s 3 %s %s%s.txt", recording_module_exe_path, liveRecordingWAV, input_live_voice_folder, liveRecordingFileName);  
		//printf("\n path: %s\n",liveRecordingCommand );
		/**************** Creating necessary file Path for data. ****************/
			sprintf(completePathOuput, "%s%s_testresult_%s.txt", input_live_voice_folder, liveRecordingFileName ,model_type_string);  
			/**************** Opening respective files. ****************/
			fp_console = fopen(completePathOuput, "w");					//to read input observation sequence
			if(fp_console == NULL){ 
					perror("\n Error: ");
					printf("\n File Names is: %s \n ", completePathOuput);
					getch();
					return EXIT_FAILURE;
			}

			do 	//record loop
			{
				printf("\n Enter To Record.");
				getch();
				printf("\n");
				/**************** Execute the Live Recording Module ****************/
				system(liveRecordingCommand);		//execute the command
				//USAGE : "Recording_Module.exe" <duration_in_seconds> <output_mono_wav_file_path> <output_text_file_path>
						
				printf("\n Playing Your Sound: "); 
				PlaySound(TEXT(liveRecordingWAV), NULL, SND_SYNC );
				//system(wavform_WAV); // create waveform of file
				printf("\n\n Is Word Correctly Spoken ?" 
					"\n\t	opt = 4: will repeat the recording process. "
					"\n\t	opt = 5: will proceed and do the testing. "
					"\n\n  --Choice :  ");
				//scanf("%c%*c",&correct_voice);
				scanf("%c",&correct_voice);

				while ((getchar()) != '\n');

			}while(correct_voice!='5');	//record loop

			printf("\n\n");
			fprintf(fp_console, "\n ----------------------- ----------------------- > LIVE TESTING : %s < ----------------------- \n",liveRecordingFileName );
			/**************** Live Testing ****************/
			int _index = live_testing_playlist(model_type_use, lang_index_begin);
			/**************** Call Playlist ****************/

			PlayList_Songs(_index);

		fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
		fprintf(fp_console, "\n <---------------------------------- ----------------------------------> END <---------------------------------- -------------------------------------->"); 
		fflush(fp_console); fclose(fp_console); 
			
		printf("\n\n p. Try Another Language.");
		printf("\n n. Return To Main Menu		\n\n  --Choice : ");
		scanf("%c%*c", &ch);
		choice=ch;
	} while (choice != 'n'); // Lang Loop
	return 1;
}//RecordingUtteranceMenu

