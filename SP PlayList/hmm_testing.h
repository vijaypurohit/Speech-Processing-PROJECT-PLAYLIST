
/**************************************************************************************************
	Replace Model in Input Folder with Output Folder.
**************************************************************************************************/
void replace_old_models_files(){

	char from_lambda_location[300], to_lambda_location[300];
	FILE *fp_infile, *fp_outfile;
	long double temp;

	for(int d=0; d<totWords; d++){

		printf("\n ---#---#---#---#---#---#---#--->>> Replacing Model: %s <---#---#---#---#---#---#---#---\n", HMM_WORDS[d]); 

// replace A
		sprintf(from_lambda_location, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[0], d);  // {output_folder/Models}+{0/}+{A_}+{1}+".txt 
		sprintf(to_lambda_location, "%s%d/%s%d.txt", input_folder, d, LambdaFileNames[0], d);  // {output_folder/Models}+{0/}+{A_}+{1}+".txt 
	
		fp_infile = fopen(from_lambda_location, "r");
		fp_outfile = fopen(to_lambda_location, "w");
			if(fp_infile == NULL || fp_outfile == NULL ){ 
				perror("\n Error: ");
				printf("\n File Names are: \nSrc: %s \nDest: %s", from_lambda_location, to_lambda_location);
				getch();
				return;
			}

		for (int si = 0; si < N; ++si){
			for (int sj = 0; sj < N; ++sj){
				fscanf(fp_infile, "%Lf",&temp);
				fprintf(fp_outfile, "%.16g\t",temp);
			}
			fprintf(fp_outfile, "\n");
		}

		fflush(fp_infile); fclose(fp_infile); 
		fflush(fp_outfile); fclose(fp_outfile); 

// replace B
		sprintf(from_lambda_location, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[1], d);  // {output_folder/Models}+{0/}+{B_}+{1}+".txt 
		sprintf(to_lambda_location, "%s%d/%s%d.txt", input_folder, d, LambdaFileNames[1], d);  // {output_folder/Models}+{0/}+{B_}+{1}+".txt 
		
		fp_infile = fopen(from_lambda_location, "r");
		fp_outfile = fopen(to_lambda_location, "w");
			if(fp_infile == NULL || fp_outfile == NULL ){ 
				perror("\n Error: ");
				printf("\n File Names are: \nSrc: %s \nDest: %s", from_lambda_location, to_lambda_location);
				getch();
				return;
			}

		for (int si = 0; si < N; ++si){
			for (int m = 0; m < M; ++m){
				fscanf(fp_infile, "%Lf",&temp);
				fprintf(fp_outfile, "%.16g\t",temp);
			}
			fprintf(fp_outfile, "\n");
		}
		fflush(fp_infile); fclose(fp_infile); 
		fflush(fp_outfile); fclose(fp_outfile); 

//replace pi
		sprintf(from_lambda_location, "%s%s/%d/%s%d.txt", output_folder, output_folder_Model_name, d, LambdaFileNames[2], d);  // {output_folder/Models}+{0/}+{Pi_}+{1}+".txt 
		sprintf(to_lambda_location, "%s%d/%s%d.txt", input_folder, d, LambdaFileNames[2], d);  // {output_folder/Models}+{0/}+{Pi_}+{1}+".txt 
		fp_infile = fopen(from_lambda_location, "r");
		fp_outfile = fopen(to_lambda_location, "w");
			if(fp_infile == NULL || fp_outfile == NULL ){ 
				perror("\n Error: ");
				printf("\n File Names are: \nSrc: %s \nDest: %s", from_lambda_location, to_lambda_location);
				getch();
				return;
			}
		for (int si = 0; si < N; ++si){
			fscanf(fp_infile, "%Lf",&temp);
			fprintf(fp_outfile, "%.16g\t",temp);
		}

		fflush(fp_infile); fclose(fp_infile); 
		fflush(fp_outfile); fclose(fp_outfile);
	}// for each Word d<totWords


}

/**************************************************************************************************
	Test Offline Utterance of the Digits
**************************************************************************************************/
void offline_testing(int test_word, unsigned int model_type_to_use){

	long double cur_alpha_probability=0;
	long double max_probability=0;
	int word_index=-1;

	int tot_words_to_use=0;
	if(model_type_to_use == InputFolderModel)
	{
		tot_words_to_use=W;
	}
	else if (model_type_to_use == OutputFolderModel)
	{
		tot_words_to_use=totWords;
	}

	offline_correct_count=0;

	for(int u=0; u<Ot; u++){
					printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~> Utterance: %s/%s_O[%d] \n", HMM_WORDS[test_word], LambdaFileNames[4], u+1);
						fprintf(fp_console, "\n ~~~~~~~~~~~~~~~~~~~~~~~~~> Utterance: %s/%s_O[%d] \n", HMM_WORDS[test_word], LambdaFileNames[4], u+1); 	 
			max_probability=0;
			cur_alpha_probability=0;
			word_index=-1;
		for(int w=0; w<tot_words_to_use; w++){
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
			printf("\n -----------------> Actual Word: %s  ", HMM_WORDS[test_word]);
				printf("\n -----------------> Word Recognized: %s\n", "NOT RECOGNIZED");
			fprintf(fp_console, "\n -----------------> Actual Word: %s  ", HMM_WORDS[test_word]);
			fprintf(fp_console, "\n -----------------> Word Recognized: %s\n", "NOT RECOGNIZED");
		}
		else
		{
			printf("\n -----------------> Actual Word: %s  ", HMM_WORDS[test_word]);
				printf("\n -----------------> Word Recognized: %s\n", HMM_WORDS[word_index]);
			fprintf(fp_console, "\n -----------------> Actual Word: %s  ", HMM_WORDS[test_word]);
			fprintf(fp_console, "\n -----------------> Word Recognized: %s\n", HMM_WORDS[word_index]);
		}	
		
		if(strcmp(HMM_WORDS[test_word], HMM_WORDS[word_index])==0)offline_correct_count++;
	}// for each u utterance

	offline_overall_count +=offline_correct_count;

	fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 
}//offline_testing

/**************************************************************************************************
	Test Live Utterance of the Digits
**************************************************************************************************/
void live_testing(unsigned int model_type_to_use){

	
	/**************** Observation Sequence Generation ****************/
	live_sequence_generation(LIVETESTING);
	/**************** Read Observation Sequence ****************/
	readObsSeqOfLiveRecording(LIVETESTING);

	/**************** Testing ****************/
	int NumOfLiveUtterance=1;

	long double cur_alpha_probability=0;
	long double max_probability=0;
	int word_index=-1;
	int tot_words_to_use=0;
	if(model_type_to_use == InputFolderModel)
	{
		tot_words_to_use=W;
	}
	else if (model_type_to_use == OutputFolderModel)
	{
		tot_words_to_use=totWords;
	}

	offline_correct_count=0;

	for(int u=0; u<NumOfLiveUtterance; u++){
					printf("\n ~~~~~~~~~~~~~~~~~~~~~~~~~> Live Utterance: %s_obs_seq_O[%d] \n", liveRecordingFileName, u+1);
						fprintf(fp_console, "\n ~~~~~~~~~~~~~~~~~~~~~~~~~> Live Utterance: %s_obs_seq_O[%d] \n", liveRecordingFileName, u+1); 	 
			max_probability=0;
			cur_alpha_probability=0;
			word_index=-1;
		for(int w=0; w<tot_words_to_use; w++){
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
		}
		else
		{
			printf("\n -----------------> Word Recognized: %s\n", HMM_WORDS[word_index]);
			fprintf(fp_console, "\n -----------------> Word Recognized: %s\n", HMM_WORDS[word_index]);
		}
		
	}// for each u utterance
	fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 
}//live_testing


