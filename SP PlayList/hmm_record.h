
/**************************************************************************************************
	Record Utterances of Speaker
**************************************************************************************************/
void RecordMyVoice(unsigned short int seq_type, int NumOfFiles,  int word_begin=0, int NumOfWords=totWords,  int fileCounter_begin=1)
{

	//unsigned short int NumOfFiles;
	char utterance_file_path[150];
	char seq_type_name[10];
	//char output_folder_name[50];
	char correct_voice;

		if(seq_type == TRAINING)
		{	
			//NumOfFiles = On;
			strcpy(seq_type_name, "TRAINING");
			//strcpy(output_folder_name, filePathInputVoiceTraining);
		}
		else if(seq_type == TESTING)
		{	
			//NumOfFiles = Ot;
			strcpy(seq_type_name, "TESTING");
			//strcpy(output_folder_name, filePathInputVoiceTesting);
		}
	
	for(int d=word_begin; d<NumOfWords; d++)
	{
		for(int fileCounter=fileCounter_begin; fileCounter <= NumOfFiles ; ++fileCounter)//iterating through all files of given digits (1 to X).
		{
			system("cls");
			/**************** Creating necessary file Path for data. ****************/
			sprintf(liveRecordingFileName, "%d/%s%d.txt", d, voice_data_prefix, fileCounter);  //file_name 0/obs_1.txt
			sprintf(utterance_file_path, "%s%s/%s", input_live_voice_folder, seq_type_name, liveRecordingFileName );  //file_name
			sprintf(liveRecordingCommand, "%s 3 %s %s", recording_module_exe_path, liveRecordingWAV, utterance_file_path);  
			//printf("\n path: %s\n",liveRecordingCommand );
			do
			{ 
				printf("\n\n ::::: To Record (3sec) For %s Utterance (%d/%d) of W[%s] %s  <------\n\n", seq_type_name, fileCounter, NumOfFiles, HMM_WORDS[d], liveRecordingFileName); 
				printf("\n ----> Press Any Key(1-9) To Begin Record:");
									getch();
				printf("\n\n");
				/**************** Execute the Live Recording Module ****************/
				system(liveRecordingCommand);		//execute the command
				//USAGE : "Recording_Module.exe" <duration_in_seconds> <output_mono_wav_file_path> <output_text_file_path>
						
				printf("\n\n Playing Sound: "); 
				PlaySound(TEXT(liveRecordingWAV), NULL, SND_SYNC );	//play the spoken sound.

				printf("\n\n Is Word Correctly Spoken?" 
					"\n\t	opt = 4: will repeat the recording process. "
					"\n\t	opt = 5: will save the file. "
					"\n\t	opt = e: exit this process. "
					"\n\n  --Choice :  ");
				//scanf("%c%*c",&correct_voice);
				scanf("%c",&correct_voice);
				while ((getchar()) != '\n');

				if(correct_voice=='e') 
					{
						remove(utterance_file_path);
						return;
						
					}

			}while(correct_voice!='5');//-------------------------------------------------------------
			
			printf("\n\n ---> File: %s", utterance_file_path) ;
			getch();
		}//end of filecounter loop -------------------------------------------------------------------------------------------------------------------
	}// for each WORD d<totWords RecordMyVoice -------------------------------------------------------------------------------------------------------------------
	
	//printf("\n ---------------------------------- --------------------------------------"); 
	//printf("\n\n :::: Please COPY/REPLACE FOLDERS (0-%d) FROM \n\t SRC: %s%s --> To --> DEST: %s", totWords, input_live_voice_folder,seq_type_name, output_folder_name); 
}//RecordMyVoice

/**************************************************************************************************
	Replace Old Utterances with New Recorded Utterances
**************************************************************************************************/
void replace_old_utterances_recordings(unsigned short int seq_type, int NumOfFiles,  int word_begin=0, int NumOfWords=totWords,  int fileCounter_begin=1)
{
	// file stream variables
	char from_location[300], to_location[300];
	FILE *fp_infile, *fp_outfile;

	//  variables
	//unsigned short NumOfFiles;
	char output_folder_name[50];
	char seq_type_name[20];
	//char dataLineToRead[20];
		long temp;
	unsigned long  total_samples=samplingRate*3; //3 num of sec of recording

	if(seq_type == TRAINING)
	{	
		//NumOfFiles = On;
		strcpy(seq_type_name, "TRAINING");
		strcpy(output_folder_name, filePathInputVoiceTraining);
	}
	else if(seq_type == TESTING)
	{	
		//NumOfFiles = Ot;
		strcpy(seq_type_name, "TESTING");
		strcpy(output_folder_name, filePathInputVoiceTesting);
	}
	

	for(int d=word_begin; d<NumOfWords; d++)
	{
		printf("\n\n ---#---#---#---#---#---#---#--->>> (%s) Replacing : %s<---#---#---#---#---#---#---#---\n", seq_type_name, HMM_WORDS[d]); 

		for(int fileCounter=fileCounter_begin; fileCounter <= NumOfFiles ; ++fileCounter)//iterating through all files of given digits (1 to X).
		{
			
			sprintf(from_location, "%s%s/%d/%s%d.txt", input_live_voice_folder, seq_type_name, d, voice_data_prefix, fileCounter);  
			sprintf(to_location, "%s%d/%s%d.txt", output_folder_name, d, voice_data_prefix, fileCounter);  
	
		fp_infile = fopen(from_location, "r");
		fp_outfile = fopen(to_location, "w");
			if(fp_infile == NULL ){ 
				perror("\n\n Error: ");
				printf("\n Src File Names is: %s \n\n\t Please Generate this Utterance & Repeate the process.", from_location);
				getch();
				return;
			}
			if(fp_outfile == NULL ){ 
				perror("\n Error: ");
				printf("\n Dest File Names is: %s", to_location);
				getch();
				return;
			}

			if(fileCounter==fileCounter_begin){
				printf("  ---->  FILEs Copied: %s ", from_location);  
			}
			else if(fileCounter==NumOfFiles)
			{
				printf("\t ---> %s%d.txt,", voice_data_prefix, fileCounter);  
			}

			//while(!feof(fp_infile)){
			//	fgets(dataLineToRead, 20, fp_infile);
			//	 (int)atoi(dataLineToRead);
			//	//fscanf(fp_infile, "%d",&temp);
			//	fprintf(fp_outfile, "%d\n",(int)atoi(dataLineToRead));
			//}
			//
			for (unsigned long int i = 0; i < total_samples; ++i){
				fscanf(fp_infile, "%ld",&temp);
				fprintf(fp_outfile, "%ld\n",temp);
			}

			fflush(fp_infile); fclose(fp_infile); 
			fflush(fp_outfile); fclose(fp_outfile); 	

		}//end of filecounter loop -------------------------------------------------------------------------------------------------------------------
	}// for each Word d<NumOfWords RecordMyVoice -------------------------------------------------------------------------------------------------------------------
	
		printf("\n\n ----------------------> Files Copied: Total(%d)\n\n", (NumOfWords-word_begin)*NumOfFiles); 
}//replace_old_utterances_recordings

/**************************************************************************************************
	Utterance Menu To Display
**************************************************************************************************/
void RecordingUtteranceMenu(){
	system("cls");
	char choice;		// choice exercised.	 
	do{
		char ch;

		int word=0, uttr_seq=1;

		printf("\n\n\n");
		system("pause");
		system("cls");

		printf("\n\n ------- -------~~ Recording Utterances ~~------- -------");

		printf("\n 1. RECORD: All WORDs i(0-%d) Utterances #(%d) for TRAINING Files. Total(%d).", totWords-1, On, totWords*On);
		printf("\n 2. RECORD: All WORDs i(0-%d) Utterances #(%d) for TESTING Files. Total(%d).", totWords-1,Ot, totWords*Ot);

		printf("\n\n 3. RECORD: Particular WORD i(?) Utterances #(%d) for TRAINING Files.",On);
		printf("\n 4. RECORD: Particular WORD i(?) Utterances #(%d) for TESTING Files.",Ot);
		
		printf("\n\n 5. RECORD: Particular WORD i(?) Particular Utterance (?) for TRAINING Files. Total(1)");
		printf("\n 6. RECORD: Particular WORD i(?) Particular Utterance (?) for TESTING Files. Total(1)");

		printf("\n\n 7. REPLACE: TRAINING Files: REPLACE ALL FOLDERS Wi(0-%d) \n\t FROM SRC(These New Recordings) TO DEST(Default Folder for Input to Model) \n\t SRC: %s%s/ --> To --> DEST: %s", totWords-1, input_live_voice_folder, "TRAINING", filePathInputVoiceTraining);
		printf("\n\n 8. REPLACE: TESTING Files: REPLACE ALL FOLDERS Wi(0-%d) \n\t FROM SRC(These New Recordings) TO DEST(Default Folder for Input to Model) \n\t SRC: %s%s/ --> To --> DEST: %s", totWords-1, input_live_voice_folder, "TESTING", filePathInputVoiceTesting);

		printf("\n\n 9. REPLACE: TRAINING Files: REPLACE Particular FOLDER Wi \n\t FROM SRC(These New Recordings) TO DEST(Default Folder for Input to Model) \n\t SRC: %s%s/ --> To --> DEST: %s", input_live_voice_folder, "TRAINING", filePathInputVoiceTraining);
		printf("\n\n t. REPLACE: TESTING Files: REPLACE Particular FOLDER Wi \n\t FROM SRC(These New Recordings) TO DEST(Default Folder for Input to Model) \n\t SRC: %s%s/ --> To --> DEST: %s",  input_live_voice_folder, "TESTING", filePathInputVoiceTesting);

		printf("\n\n n. Return To Main HMM Menu		\n\n  --Choice : ");
		scanf("%c%*c", &ch);
		printf("\n <-------->");
		switch (ch) {
			case '1' : 
//RecordMyVoice(unsigned short int seq_type, int NumOfFiles,  int word_begin=0, int NumOfWords=totWords,  int fileCounter_begin=1, bool loopAll=true)
							RecordMyVoice(TRAINING, On);
				break;
			case '2' : 
							RecordMyVoice(TESTING, Ot);
				break;
			case '3' : 
						printf("\n Enter Particular WORD Index(0-%d) to Generate Training Utterances: ", totWords-1);
							scanf("%d%*c", &word);
						RecordMyVoice(TRAINING, On, word, word+1);
		
				break;
			case '4' :	printf("\n Enter Particular WORD Index(0-%d) to Generate Testing Utterances: ", totWords-1);
							scanf("%d%*c", &word);
						RecordMyVoice(TESTING, Ot, word, word+1);
				break;
			case '5' : 
						printf("\n Enter Particular WORD Index(0-%d) : ", totWords-1);
							scanf("%d%*c", &word);
						printf("\n Enter Particular Utterance (1-%d) : ", On);
							scanf("%d%*c", &uttr_seq);
						RecordMyVoice(TRAINING, uttr_seq, word, word+1, uttr_seq);
				break;
			case '6' : 
						printf("\n Enter Particular WORD Index(0-%d) : ", totWords-1);
							scanf("%d%*c", &word);
						printf("\n Enter Particular Utterance (1-%d) : ", On);
							scanf("%d%*c", &uttr_seq);
						RecordMyVoice(TESTING, uttr_seq, word, word+1, uttr_seq);
				break;
			case '7' : //replace_old_utterances_recordings(unsigned short int seq_type, int NumOfFiles,  int word_begin=0, int NumOfWords=totWords,  int fileCounter_begin=1)

							replace_old_utterances_recordings(TRAINING, On);
				break;
			case '8' : 
							replace_old_utterances_recordings(TESTING, Ot);
				break;
			case '9' : //replace_old_utterances_recordings(unsigned short int seq_type, int NumOfFiles,  int word_begin=0, int NumOfWords=totWords,  int fileCounter_begin=1)
						printf("\n Enter Particular WORD Index(0-%d) : ", totWords-1);
							scanf("%d%*c", &word);
							replace_old_utterances_recordings(TRAINING, On,word, word+1);
				break;
			case 't' : 
						printf("\n Enter Particular WORD Index(0-%d) : ", totWords-1);
									scanf("%d%*c", &word);
							replace_old_utterances_recordings(TESTING, Ot,word, word+1);
				break;
			case 'n' :   return;  
				break;
			default  :   printf("\n--Invalid Choice. Enter Again \n");
		}//switch
		choice=ch;
	} while (choice != 'n');

}//RecordingUtteranceMenu

/**************************************************************************************************
	Average out the word Converged one model with its existing word model 
**************************************************************************************************/
void output_livetrain_converged_lambdaABPi_to_each_file(int d){
	FILE *fp_ind_out, *fp_ind_in;;
	char completePathIndOutFile[200], completePathIndInFile[200];
	
// Save PI
	sprintf(completePathIndOutFile, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[2], d);  
	fp_ind_out = fopen(completePathIndOutFile, "w");				//to read input codebook
	if(fp_ind_out == NULL){ 
		perror("\n Error: ");
		printf("\n File Name is: %s", completePathIndOutFile);
		getch();
		return;
	}

	for (int si = 0; si < N; ++si){
		fprintf(fp_ind_out, "%.16g\t",PI[si]);
	}

	fflush(fp_ind_out); fclose(fp_ind_out); 

//*************** take averaged lambda
//READ OLD OUTPUT LAMBDA A And Average out it
	sprintf(completePathIndInFile, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[0], d);  // {completePathInput}+{A_}+{1}+".txt 
	fp_ind_in = fopen(completePathIndInFile, "r");				//to read input A from lamda
		if(fp_ind_in == NULL){ 
			perror("\nError: ");
			printf("\nREAD OLD OUTPUT LAMBDA A File Name is: %s\n", completePathIndInFile);
			getch();
			return;
		}	
	for (int si = 0; si < N; ++si){
		for (int sj = 0; sj < N; ++sj){
				fscanf(fp_ind_in,"%Lf",&A_Prev[si][sj]);
				A[si][sj]=(A[si][sj]+A_Prev[si][sj])/2;
			}
	}
	fflush(fp_ind_in); fclose(fp_ind_in); 

	


//READ OLD OUTPUT LAMBDA B And Average out it
	sprintf(completePathIndInFile, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[1], d);  
		fp_ind_in = fopen(completePathIndInFile, "r");				//to read input B from lamda
			if(fp_ind_in == NULL){ 
				perror("\nError: ");
				printf("\nREAD OLD OUTPUT LAMBDA B File Name is: %s\n", completePathIndInFile);
				getch();
				return;
			}	
		
		for (int si = 0; si < N; ++si){
			for (int m = 0; m < M; ++m){
					fscanf(fp_ind_in,"%Lf",&B_Prev[si][m]);
					B[si][m]=(B[si][m]+B_Prev[si][m])/2;
				}
		}
		fflush(fp_ind_in); fclose(fp_ind_in); 


//*************** make stochastic
		make_lambda_stochastic();

//Save A
	sprintf(completePathIndOutFile, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[0], d);  
	fp_ind_out = fopen(completePathIndOutFile, "w");			
	if(fp_ind_out == NULL){ 
		perror("\n Error: ");
		printf("\n File Name is: %s", completePathIndOutFile);
		getch();
		return;
	}
	for (int si = 0; si < N; ++si){
		for (int sj = 0; sj < N; ++sj){
			fprintf(fp_ind_out, "%.16g\t",A[si][sj]);
		}
		fprintf(fp_ind_out, "\n");
	}
	fflush(fp_ind_out); fclose(fp_ind_out); 

//Save B
	sprintf(completePathIndOutFile, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[1], d);  
	fp_ind_out = fopen(completePathIndOutFile, "w");			
	if(fp_ind_out == NULL){ 
		perror("\n Error: ");
		printf("\n File Name is: %s", completePathIndOutFile);
		getch();
		return;
	}

	for (int si = 0; si < N; ++si){
		for (int m = 0; m < M; ++m){
		
			fprintf(fp_ind_out, "%.16g\t", B[si][m]);
		}
		fprintf(fp_ind_out, "\n");
	}
	fflush(fp_ind_out); fclose(fp_ind_out); 

}


void LiveRecordingTrainingTheOutputModel(int word)
{
	char correct_voice;

	printf("\n Duration 3 sec: \n"); 
	timestamp = time(NULL);
	//timestamp = 30;

	/**************** Creating necessary file Path for data. ****************/
	sprintf(liveRecordingFileName, "word_%s_livetrain_%ld", HMM_WORDS[word], timestamp);  //file_name
	sprintf(liveRecordingCommand, "%s 3 %s %sLIVE_TRAIN/%s.txt", recording_module_exe_path, liveRecordingWAV, input_live_voice_folder, liveRecordingFileName);  
	//printf("\n path: %s\n",liveRecordingCommand );
	/**************** Creating necessary file Path for data. ****************/
	sprintf(completePathOuput, "%sLIVE_TRAIN/%s_test_result.txt", input_live_voice_folder, liveRecordingFileName);  
	/**************** Opening respective files. ****************/
	fp_console = fopen(completePathOuput, "w");					//to read input observation sequence
	if(fp_console == NULL){ 
			perror("\n Error: ");
			printf("\n File Names is: %s \n ", completePathOuput);
			getch();
			return;
	}

	do
	{
		printf("\n Enter To Record.");
		getch();
		printf("\n");
		/**************** Execute the Live Recording Module ****************/
		system(liveRecordingCommand);		//execute the command
		//USAGE : "Recording_Module.exe" <duration_in_seconds> <output_mono_wav_file_path> <output_text_file_path>
						
		printf("\n Playing Sound: "); 
		PlaySound(TEXT(liveRecordingWAV), NULL, SND_SYNC );
		//system(wavform_WAV); // create waveform of file
		printf("\n\n Is Word Correctly Spoken ?" 
			"\n\t	opt = 4: will repeat the recording process. "
			"\n\t	opt = 5: will proceed and do the training. "
			"\n\n  --Choice :  ");
		//scanf("%c%*c",&correct_voice);
		scanf("%c",&correct_voice);

		while ((getchar()) != '\n');

	}while(correct_voice!='5');
						
	printf("\n\n");

	fprintf(fp_console, "\n ----------------------- ----------------------- > LIVE TRAINING : %s < ----------------------- \n",liveRecordingFileName );
	
	/**************** Observation Sequence Generation ****************/
	live_sequence_generation(LIVETRAINING);
	/**************** Read Observation Sequence ****************/
	readObsSeqOfLiveRecording(LIVETRAINING);
	covergence_procedure(1);
	output_livetrain_converged_lambdaABPi_to_each_file(word);
		
	fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
	fprintf(fp_console, "\n <---------------------------------- ----------------------------------> END <---------------------------------- -------------------------------------->"); 
	fflush(fp_console); fclose(fp_console); 
}




