/*
 *  pipelinepdscommand.cpp
 *  Mothur
 *
 *  Created by westcott on 10/5/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */

#include "pipelinepdscommand.h"
#include "sffinfocommand.h"
#include "commandoptionparser.hpp"

//**********************************************************************************************************************
vector<string> PipelineCommand::setParameters(){	
	try {
		CommandParameter psff("sff", "InputTypes", "", "", "none", "oneRequired", "pipe","",false,false,true); parameters.push_back(psff);
		CommandParameter poligos("oligos", "InputTypes", "", "", "none", "oneRequired", "pipe","",false,false,true); parameters.push_back(poligos);
		CommandParameter palign("align", "InputTypes", "", "", "none", "oneRequired", "pipe","",false,false,true); parameters.push_back(palign);
		CommandParameter pchimera("chimera", "InputTypes", "", "", "none", "oneRequired", "pipe","",false,false,true); parameters.push_back(pchimera);
		CommandParameter pclassify("classify", "InputTypes", "", "", "none", "oneRequired", "pipe","",false,false,true); parameters.push_back(pclassify);
		CommandParameter ptaxonomy("taxonomy", "InputTypes", "", "", "none", "oneRequired", "pipe","",false,false,true); parameters.push_back(ptaxonomy);
		CommandParameter ppipeline("pipeline", "InputTypes", "", "", "none", "oneRequired", "none","",false,false,true); parameters.push_back(ppipeline);
		CommandParameter pprocessors("processors", "Number", "", "1", "", "", "","",false,false,true); parameters.push_back(pprocessors);
		CommandParameter pseed("seed", "Number", "", "0", "", "", "","",false,false); parameters.push_back(pseed);
        CommandParameter pinputdir("inputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(pinputdir);
		CommandParameter poutputdir("outputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(poutputdir);
		
		vector<string> myArray;
		for (int i = 0; i < parameters.size(); i++) {	myArray.push_back(parameters[i].name);		}
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "setParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
string PipelineCommand::getHelpString(){	
	try {
		string helpString = "";
		helpString += "The pipeline.pds command is designed to guide you through your analysis using mothur.\n"; 
		helpString += "The pipeline.pds command parameters are pipeline, sff, oligos, align, chimera, classify, taxonomy and processors.\n"; 
		helpString += "The sff parameter allows you to enter your sff file. It is required, if not using pipeline parameter.\n"; 
		helpString += "The oligos parameter allows you to enter your oligos file. It is required, if not using pipeline parameter.\n"; 
		helpString += "The align parameter allows you to enter a template to use with the aligner. It is required, if not using pipeline parameter.\n"; 
		helpString += "The chimera parameter allows you to enter a template to use for chimera detection. It is required, if not using pipeline parameter.\n"; 
		helpString += "The classify parameter allows you to enter a template to use for classification. It is required, if not using pipeline parameter.\n"; 
		helpString += "The taxonomy parameter allows you to enter a taxonomy file for the classify template to use for classification. It is required, if not using pipeline parameter.\n"; 
		helpString += "The processors parameter allows you to specify the number of processors to use. The default is 1.\n";
		helpString += "The pipeline parameter allows you to enter your own pipeline file. This file should look like a mothur batchfile, but where you would be using a mothur generated file, you can use current instead.\n"; 
		helpString += "Example: trim.seqs(processors=8, allfiles=T, maxambig=0, maxhomop=8, flip=T, bdiffs=1, pdiffs=2, qwindowaverage=35, qwindowsize=50, fasta=may1.v13.fasta, oligos=may1.v13.oligos, qfile=may1.v13.qual)\n";
		helpString += "then, you could enter unique.seqs(fasta=current), and mothur would use the .trim.fasta file from the trim.seqs command. \n";
		helpString += "then you could enter align.seqs(candidate=current, template=silva.v13.align, processors=8). , and mothur would use the .trim.unique.fasta file from the unique.seqs command. \n";
		helpString += "If no pipeline file is given then mothur will use Pat's pipeline. \n";
		helpString += "Here is a list of the commands used in Pat's pipeline.\n"; 
		helpString += "All paralellized commands will use the processors you entered.\n"; 
		helpString += "The sffinfo command takes your sff file and extracts the fasta and quality files.\n"; 
		helpString += "The trim.seqs command uses your oligos file and the quality and fasta files generated by sffinfo.\n"; 
		helpString += "The trim.seqs command sets the following parameters: allfiles=T, maxambig=0, maxhomop=8, flip=T, bdiffs=1, pdiffs=2, qwindowaverage=35, qwindowsize=50.\n"; 
		helpString += "The unique.seqs command uses the trimmed fasta file and removes redundant sequences, don't worry the names file generated by unique.seqs will be used in the pipeline to make sure they are included.\n"; 
		helpString += "The align.seqs command aligns the unique sequences using the aligners default options. \n"; 
		helpString += "The screen.seqs command screens the sequences using optimize=end-minlength. \n"; 
		helpString += "The pipeline uses chimera.slayer to detect chimeras using the default options. \n";
		helpString += "The pipeline removes all sequences determined to be chimeric by chimera.slayer. \n";
		helpString += "The filter.seqs command filters the sequences using vertical=T, trump=. \n"; 
		helpString += "The unique.seqs command uses the filtered fasta file and name file to remove sequences that have become redundant after filtering.\n"; 
		helpString += "The pre.cluster command clusters sequences that have no more than 2 differences.\n"; 
		helpString += "The dist.seqs command is used to generate a column and phylip formatted distance matrix using cutoff=0.20 for column.\n"; 
		helpString += "The pipeline uses cluster with method=average, hard=T. \n";
		helpString += "The classify.seqs command is used to classify the sequences using the bayesian method with a cutoff of 80.\n"; 
		helpString += "The phylotype command is used to cluster the sequences based on their classification.\n"; 
		helpString += "The clearcut command is used to generate a tree using neighbor=T. \n";
		helpString += "The summary.single and summary.shared commands are run on the otu files from cluster and phylotype commands. \n";
		helpString += "The summary.shared command uses calc=sharednseqs-sharedsobs-sharedchao-sharedace-anderberg-jclass-jest-kulczynski-kulczynskicody-lennon-ochiai-sorclass-sorest-whittaker-braycurtis-jabund-morisitahorn-sorabund-thetan-thetayc. \n";
		helpString += "The summary.single command uses calc=nseqs-sobs-coverage-bergerparker-chao-ace-jack-bootstrap-boneh-efron-shen-solow-shannon-npshannon-invsimpson-qstat-simpsoneven-shannoneven-heip-smithwilson. \n";
		helpString += "The classify.otu command is used to get the concensus taxonomy for otu files from cluster and phylotype commands. \n";
		helpString += "The phylo.diversity command run on the tree generated by clearcut with rarefy=T, iters=100. \n";
		helpString += "The unifrac commands are also run on the tree generated by clearcut with random=F, distance=T. \n";
		helpString += "\n";
		return helpString;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "getHelpString");
		exit(1);
	}
}


//**********************************************************************************************************************
PipelineCommand::PipelineCommand(string option) {
	try {
		cFactory = CommandFactory::getInstance();
		abort = false; calledHelp = false;   
		
		//allow user to run help
		if(option == "help") { help(); abort = true; calledHelp = true; }
		else if(option == "citation") { citation(); abort = true; calledHelp = true;}
		
		else {
			vector<string> myArray = setParameters();
			
			OptionParser parser(option);
			map<string, string> parameters = parser.getParameters(); 
			
			ValidParameters validParameter;
			map<string, string>::iterator it;
			
			//check to make sure all parameters are valid for command
			for (it = parameters.begin(); it != parameters.end(); it++) { 
				if (validParameter.isValidParameter(it->first, myArray, it->second) != true) {  abort = true;  }
			}
			
			//if the user changes the input directory command factory will send this info to us in the output parameter 
			string inputDir = validParameter.validFile(parameters, "inputdir", false);		
			if (inputDir == "not found"){	inputDir = "";		}
			else {
				string path;
				it = parameters.find("sff");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["sff"] = inputDir + it->second;		}
				}
				
				it = parameters.find("oligos");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["oligos"] = inputDir + it->second;		}
				}
				
				it = parameters.find("align");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["align"] = inputDir + it->second;		}
				}
				
				it = parameters.find("chimera");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["chimera"] = inputDir + it->second;		}
				}
				
				it = parameters.find("classify");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["classify"] = inputDir + it->second;		}
				}
				
				it = parameters.find("taxonomy");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["taxonomy"] = inputDir + it->second;		}
				}
				
				it = parameters.find("pipeline");
				//user has given a template file
				if(it != parameters.end()){ 
					path = m->hasPath(it->second);
					//if the user has not given a path then, add inputdir. else leave path alone.
					if (path == "") {	parameters["pipeline"] = inputDir + it->second;		}
				}
			}
			
			outputDir = validParameter.validFile(parameters, "outputdir", false);		if (outputDir == "not found"){	outputDir = "";	}
			
			pipeFilename = validParameter.validFile(parameters, "pipeline", true);
			if (pipeFilename == "not found") { pipeFilename = "";  }
			else if (pipeFilename == "not open") { pipeFilename = ""; abort = true; }
			
			string temp = validParameter.validFile(parameters, "processors", false);	if (temp == "not found"){	temp = m->getProcessors();	}
			m->setProcessors(temp);
			m->mothurConvert(temp, processors);
			
			if (pipeFilename != "") {
				abort = readUsersPipeline();
			}else{
				sffFile = validParameter.validFile(parameters, "sff", true);
				if (sffFile == "not found") { m->mothurOut("sff is a required parameter for the pipeline command."); m->mothurOutEndLine(); abort = true;  }
				else if (sffFile == "not open") { sffFile = ""; abort = true; }
				else { m->setSFFFile(sffFile); }
					
				oligosFile = validParameter.validFile(parameters, "oligos", true);
				if (oligosFile == "not found") { m->mothurOut("oligos is a required parameter for the pipeline command."); m->mothurOutEndLine(); abort = true;  }
				else if (oligosFile == "not open") { oligosFile = ""; abort = true; }
					
				alignFile = validParameter.validFile(parameters, "align", true);
				if (alignFile == "not found") { m->mothurOut("align is a required parameter for the pipeline command. Please provide the template to align with."); m->mothurOutEndLine(); abort = true;  }
				else if (alignFile == "not open") { alignFile = ""; abort = true; }

				chimeraFile = validParameter.validFile(parameters, "chimera", true);
				if (chimeraFile == "not found") { m->mothurOut("chimera is a required parameter for the pipeline command. Please provide the template to check for chimeras with."); m->mothurOutEndLine(); abort = true;  }
				else if (chimeraFile == "not open") { chimeraFile = ""; abort = true; }

				classifyFile = validParameter.validFile(parameters, "classify", true);
				if (classifyFile == "not found") { m->mothurOut("classify is a required parameter for the pipeline command. Please provide the template to use with the classifier."); m->mothurOutEndLine(); abort = true;  }
				else if (classifyFile == "not open") { classifyFile = ""; abort = true; }

				taxonomyFile = validParameter.validFile(parameters, "taxonomy", true);
				if (taxonomyFile == "not found") { m->mothurOut("taxonomy is a required parameter for the pipeline command."); m->mothurOutEndLine(); abort = true;  }
				else if (taxonomyFile == "not open") { taxonomyFile = ""; abort = true; }
			}
		}

	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "PipelineCommand");
		exit(1);
	}
}
//**********************************************************************************************************************

int PipelineCommand::execute(){
	try {
		if (abort == true) { if (calledHelp) { return 0; }  return 2;	}
		
		int start = time(NULL);
		
		if (pipeFilename == "") { 
			createPatsPipeline(); 
			
			//run Pats pipeline
			for (int i = 0; i < commands.size(); i++) {
				m->mothurOutEndLine(); m->mothurOut("mothur > " + commands[i]); m->mothurOutEndLine();
							
				if (m->control_pressed) { return 0; }

				CommandOptionParser parser(commands[i]);
				string commandName = parser.getCommandString();
				string options = parser.getOptionString();
				
				//executes valid command
				Command* command = cFactory->getCommand(commandName, options, "pipe");
				command->execute();
				
				//add output files to list
				map<string, vector<string> > thisCommandsFile = command->getOutputFiles();
				map<string, vector<string> >::iterator itMade;
				for (itMade = thisCommandsFile.begin(); itMade != thisCommandsFile.end(); itMade++) { 
					vector<string> temp = itMade->second; 
					for (int j = 0; j < temp.size(); j++) { outputNames.push_back(temp[j]); }
				}

			}
			
		}else {  runUsersPipeline(); }
		
		if (m->control_pressed) { return 0; }
		
		m->mothurOut("It took " + toString(time(NULL) - start) + " secs to run the pipeline analysis."); m->mothurOutEndLine(); m->mothurOutEndLine();
		
		m->mothurOutEndLine();
		m->mothurOut("Output File Names: "); m->mothurOutEndLine();
		for (int i = 0; i < outputNames.size(); i++) {	m->mothurOut(outputNames[i]); m->mothurOutEndLine();	}
		m->mothurOutEndLine();
		
		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "execute");
		exit(1);
	}
}
//**********************************************************************************************************************

bool PipelineCommand::readUsersPipeline(){
	try {
		
		ifstream in;
		m->openInputFile(pipeFilename, in);
		
		string nextCommand = "";
		
		map<string, vector<string> > mothurMadeFiles;
		
		while(!in.eof()) {
			nextCommand = m->getline(in); m->gobble(in);

			if (nextCommand[0] != '#') {
				bool error = false;
				
				string commandName, options;
				error = parseCommand(nextCommand, commandName, options);
				
				if (error) { in.close(); return error; }
				if (commandName == "pipeline.pds") { m->mothurOut("Cannot run the pipeline.pds command from inside the pipeline.pds command."); m->mothurOutEndLine(); in.close(); return true; }
				
				error = checkForValidAndRequiredParameters(commandName, options, mothurMadeFiles);
				
				if (error) { in.close(); return error; }
			}
		}
		
		in.close();
		
		return false;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "readUsersPipeline");
		exit(1);
	}
}
//**********************************************************************************************************************

bool PipelineCommand::parseCommand(string nextCommand, string& name, string& options){
	try {
		CommandOptionParser parser(nextCommand);
		name = parser.getCommandString();
		options = parser.getOptionString();
		
		if (name == "") { return true; } //name == "" if () are not right
		
		return false;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "parseCommand");
		exit(1);
	}
}
//**********************************************************************************************************************

bool PipelineCommand::checkForValidAndRequiredParameters(string name, string options, map<string, vector<string> >& mothurMadeFiles){
	try {
				
		if (name == "system") { return false; }
		
		//get shell of the command so we can check to make sure its valid without running it
		Command* command = cFactory->getCommand(name);
			
		//check to make sure all parameters are valid for command
		vector<string> validParameters = command->setParameters();
		
		OptionParser parser(options);
		map<string, string> parameters = parser.getParameters(); 
			
		ValidParameters validParameter;
		map<string, string>::iterator it;
		map<string, vector<string> >::iterator itMade;
			
		for (it = parameters.begin(); it != parameters.end(); it++) { 
			
			if (validParameter.isValidParameter(it->first, validParameters, it->second) != true) {  return true;  } // not valid
			if (it->second == "current") {
				itMade = mothurMadeFiles.find(it->first);
				
				if (itMade == mothurMadeFiles.end()) {  
					m->mothurOut("You have the " + it->first + " listed as a current file for the " + name + " command, but it seems mothur will not make that file in your current pipeline, please correct."); m->mothurOutEndLine();
					return true;
				}
			}
		}
			
		//is the command missing any required
		vector<CommandParameter> commandParameters = command->getParameters();
		vector<string> requiredParameters;
		for (int i = 0; i < commandParameters.size(); i++) {
			if (commandParameters[i].required) {
				requiredParameters.push_back(commandParameters[i].name);
			}
		}
		
		for (int i = 0; i < requiredParameters.size(); i++) { 
			it = parameters.find(requiredParameters[i]);
			
			if (it == parameters.end()) { 
				
				string paraToLookFor = requiredParameters[i];
				
				//does mothur have a current file for this?
				itMade = mothurMadeFiles.find(requiredParameters[i]);
				
				if (itMade == mothurMadeFiles.end()) {
					m->mothurOut(name + " requires the " + requiredParameters[i] + " parameter, please correct."); m->mothurOutEndLine(); 
			
				}
			}
		}

		
		//update MothurMade
		map<string, vector<string> > thisCommandsFile = command->getOutputFiles();
		for (itMade = thisCommandsFile.begin(); itMade != thisCommandsFile.end(); itMade++) { 
			mothurMadeFiles[itMade->first] = itMade->second; //adds any new types
		}
			
		return false;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "checkForValidAndRequiredParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
int PipelineCommand::runUsersPipeline(){
	try {
		ifstream in;
		m->openInputFile(pipeFilename, in);
		
		string nextCommand = "";
		
		map<string, vector<string> > mothurMadeFiles;
		
		while(!in.eof()) {
			nextCommand = m->getline(in);  m->gobble(in);
		
			if (nextCommand[0] != '#') {
				CommandOptionParser parser(nextCommand);
				string commandName = parser.getCommandString();
				string options = parser.getOptionString();
					
				if ((options != "") && (commandName != "system")) {
					bool error = fillInMothurMade(options, mothurMadeFiles);
					if (error) { in.close(); return 0; }
				}
				
				m->mothurOutEndLine(); m->mothurOut("mothur > " + commandName + "(" + options + ")"); m->mothurOutEndLine();
								
				if (m->control_pressed) { return 0; }
					
				//executes valid command
				Command* command = cFactory->getCommand(commandName, options, "pipe");
				command->execute();
				
				//add output files to list
				map<string, vector<string> > thisCommandsFile = command->getOutputFiles();
				map<string, vector<string> >::iterator itMade;
				map<string, vector<string> >::iterator it;
				for (itMade = thisCommandsFile.begin(); itMade != thisCommandsFile.end(); itMade++) { 
		
					vector<string> temp = itMade->second;
					for (int k = 0; k < temp.size(); k++) { outputNames.push_back(temp[k]); }  //
					
					//update Mothur Made for each file
					it = mothurMadeFiles.find(itMade->first);
					
					if (it == mothurMadeFiles.end()) { //new type
			
						mothurMadeFiles[itMade->first] = temp;
				
					}else{ //update existing type
						vector<string> oldFileNames = it->second;
						//look at new files, see if an old version of the file exists, if so update, else just add.
						//for example you may have abrecovery.fasta and amazon.fasta as old files and you created a new amazon.trim.fasta.
						
						for (int k = 0; k < temp.size(); k++) {
							
							//get base name
							string root = m->getSimpleName(temp[k]);
							string individual = "";
							for(int i=0;i<root.length();i++){
								if(root[i] == '.'){
									root = individual;
									break;
								}else{
									individual += root[i];
								}
							}
							
							//look for that base name in oldfiles
							int spot = -1;
							for (int l = 0; l < oldFileNames.size(); l++) {
								int pos = oldFileNames[l].find(root);
								if (pos != string::npos) {
									spot = l;
									break;
								}
							}
							
							//if you found it update it, else add it
							if (spot != -1) {
								mothurMadeFiles[it->first][spot] = temp[k];
							}else{
								mothurMadeFiles[it->first].push_back(temp[k]);
							}
						}
					}
				}
			}
		}
		
		in.close();
		
		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "runUsersPipeline");
		exit(1);
	}
}
//**********************************************************************************************************************
bool PipelineCommand::fillInMothurMade(string& options, map<string, vector<string> >& mothurMadeFiles){
	try {
		
		OptionParser parser(options);
		map<string, string> parameters = parser.getParameters(); 
		map<string, string>::iterator it;
		map<string, vector<string> >::iterator itMade;
		
		options = "";
		
		//fill in mothurmade filenames
		for (it = parameters.begin(); it != parameters.end(); it++) { 
			string paraType = it->first;
			string tempOption = it->second;
			
			if (tempOption == "current") {
			
				itMade = mothurMadeFiles.find(paraType);
				
				if (itMade == mothurMadeFiles.end()) { 
					m->mothurOut("Looking for a current " + paraType + " file, but it seems mothur has not made that file type in your current pipeline, please correct."); m->mothurOutEndLine();
					return true;
				}else{
					vector<string> temp = itMade->second;
					
					if (temp.size() > 1) {
						//ask user which file to use
						m->mothurOut("More than one file has been created for the " + paraType + " parameter. "); m->mothurOutEndLine();
						for (int i = 0; i < temp.size(); i++) {
							m->mothurOut(toString(i) + " - " + temp[i]); m->mothurOutEndLine();
						}
						
						m->mothurOut("Please select the number of the file you would like to use: ");
						int num = 0;
						cin >> num;
						m->mothurOutJustToLog(toString(num)); m->mothurOutEndLine();
						
						if ((num < 0) || (num > (temp.size()-1))) { m->mothurOut("Not a valid response, quitting."); m->mothurOutEndLine(); return true; }
						else {
							tempOption = temp[num];
						}
				
						//clears buffer so next command doesn't have error
						string s;	
						getline(cin, s);
						
						vector<string> newTemp;
						for (int i = 0; i < temp.size(); i++) {
							if (i == num) { newTemp.push_back(temp[i]); }
							else {
								m->mothurOut("Would you like to remove " + temp[i] + " as an option for " + paraType + ", (y/n): "); m->mothurOutEndLine();
								string response;
								cin >> response;
								m->mothurOutJustToLog(response); m->mothurOutEndLine();
							
								if (response == "n") {  newTemp.push_back(temp[i]); }
							
								//clears buffer so next command doesn't have error
								string s;	
								getline(cin, s);
							}
						}
						
						mothurMadeFiles[paraType] = newTemp;
						
						
					}else if (temp.size() == 0){
						m->mothurOut("Sorry, we seem to think you created a " + paraType + " file, but it seems mothur doesn't have a filename."); m->mothurOutEndLine();
						return true;
					}else{
						tempOption = temp[0];
					}
				}
			}
			
			options += it->first + "=" + tempOption + ", ";
		}
		
		//rip off extra comma
		options = options.substr(0, (options.length()-2));
		
		return false;
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "fillInMothurMade");
		exit(1);
	}
}

//**********************************************************************************************************************
void PipelineCommand::createPatsPipeline(){
	try {
		
		//sff.info command
		string thisCommand = "sffinfo(sff=" + sffFile + ")";
		commands.push_back(thisCommand);
		
		//trim.seqs command
		string fastaFile = m->getRootName(m->getSimpleName(sffFile)) + "fasta";
		string qualFile = m->getRootName(m->getSimpleName(sffFile)) + "qual";
		thisCommand = "trim.seqs(processors=" + toString(processors) + ", fasta=current, allfiles=T, maxambig=0, maxhomop=8, flip=T, bdiffs=1, pdiffs=2, qwindowaverage=35, qwindowsize=50, oligos=" + oligosFile + ", qfile=current)";
		commands.push_back(thisCommand);
		
		//unique.seqs
		string groupFile = m->getRootName(m->getSimpleName(fastaFile)) + "groups";
		qualFile =  m->getRootName(m->getSimpleName(fastaFile)) + "trim.qual";
		fastaFile =  m->getRootName(m->getSimpleName(fastaFile)) + "trim.fasta";
		thisCommand = "unique.seqs(fasta=current)"; 
		commands.push_back(thisCommand);
		
		//align.seqs
		string nameFile = m->getRootName(m->getSimpleName(fastaFile)) + "names";
		fastaFile = m->getRootName(m->getSimpleName(fastaFile)) + "unique" + m->getExtension(fastaFile);
		thisCommand = "align.seqs(processors=" + toString(processors) + ", candidate=current, template=" + alignFile + ")";
		commands.push_back(thisCommand);
		
		//screen.seqs
		fastaFile = m->getRootName(m->getSimpleName(fastaFile)) + "align";
		thisCommand = "screen.seqs(processors=" + toString(processors) + ", fasta=current, name=current, group=current, optimize=end-minlength)";
		commands.push_back(thisCommand);
		
		//chimera.slayer
		fastaFile = m->getRootName(m->getSimpleName(fastaFile)) + "good" + m->getExtension(fastaFile);
		nameFile = m->getRootName(m->getSimpleName(nameFile)) + "good" + m->getExtension(nameFile);
		groupFile = m->getRootName(m->getSimpleName(groupFile)) + "good" + m->getExtension(groupFile);
		thisCommand = "chimera.slayer(processors=" + toString(processors) + ", fasta=current, template=" + chimeraFile + ")";
		commands.push_back(thisCommand);
		
		//remove.seqs
		string accnosFile = m->getRootName(m->getSimpleName(fastaFile))  + "slayer.accnos";
		thisCommand = "remove.seqs(fasta=current, name=current, group=current, accnos=current, dups=T)";
		commands.push_back(thisCommand);
		
		//filter.seqs
		nameFile = m->getRootName(m->getSimpleName(nameFile)) + "pick" + m->getExtension(nameFile);
		groupFile = m->getRootName(m->getSimpleName(groupFile)) + "pick" + m->getExtension(groupFile);
		fastaFile = m->getRootName(m->getSimpleName(fastaFile)) + "pick" + m->getExtension(fastaFile);
		thisCommand = "filter.seqs(processors=" + toString(processors) + ", fasta=current, vertical=T, trump=.)";
		commands.push_back(thisCommand);
		
		//unique.seqs
		fastaFile =  m->getRootName(m->getSimpleName(fastaFile)) + "filter.fasta";
		thisCommand = "unique.seqs(fasta=current, name=current)"; 
		commands.push_back(thisCommand);
		
		//pre.cluster
		nameFile = m->getRootName(m->getSimpleName(fastaFile)) + "names";
		fastaFile = m->getRootName(m->getSimpleName(fastaFile)) + "unique" + m->getExtension(fastaFile);
		thisCommand = "pre.cluster(fasta=current, name=current, diffs=2)"; 
		commands.push_back(thisCommand);
		
		//dist.seqs
		nameFile = m->getRootName(m->getSimpleName(fastaFile)) + "precluster.names";
		fastaFile = m->getRootName(m->getSimpleName(fastaFile)) + "precluster" + m->getExtension(fastaFile);
		thisCommand = "dist.seqs(processors=" + toString(processors) + ", fasta=current, cutoff=0.20)";
		commands.push_back(thisCommand);
		
		//dist.seqs
		string columnFile = m->getRootName(m->getSimpleName(fastaFile)) + "dist";
		thisCommand = "dist.seqs(processors=" + toString(processors) + ", fasta=current, output=lt)";
		commands.push_back(thisCommand);
		
		//read.dist
		string phylipFile = m->getRootName(m->getSimpleName(fastaFile)) + "phylip.dist";
		thisCommand = "read.dist(column=current, name=current)";
		commands.push_back(thisCommand);
		
		//cluster
		thisCommand = "cluster(method=average, hard=T)";
		commands.push_back(thisCommand);
		
		string listFile = m->getRootName(m->getSimpleName(columnFile)) + "an.list";
		string rabundFile = m->getRootName(m->getSimpleName(columnFile)) + "an.rabund";
		
		//degap.seqs
		thisCommand = "degap.seqs(fasta=current)";
		commands.push_back(thisCommand);
		
		//classify.seqs
		fastaFile = m->getRootName(m->getSimpleName(fastaFile)) + "ng.fasta";
		thisCommand = "classify.seqs(processors=" + toString(processors) + ", fasta=current, name=current, template=" + classifyFile + ", taxonomy=" + taxonomyFile + ", cutoff=80)";
		commands.push_back(thisCommand);
		
		string RippedTaxName = m->getRootName(m->getSimpleName(taxonomyFile));
		RippedTaxName = m->getExtension(RippedTaxName.substr(0, RippedTaxName.length()-1));
		if (RippedTaxName[0] == '.') { RippedTaxName = RippedTaxName.substr(1, RippedTaxName.length()); }
		RippedTaxName +=  "."; 
		
		string fastaTaxFile = m->getRootName(m->getSimpleName(fastaFile)) + RippedTaxName + "taxonomy";
		string taxSummaryFile = m->getRootName(m->getSimpleName(fastaFile)) + RippedTaxName + "tax.summary";
		
		//phylotype
		thisCommand = "phylotype(taxonomy=current, name=current)";
		commands.push_back(thisCommand);
		
		string phyloListFile = m->getRootName(m->getSimpleName(fastaTaxFile)) + "tx.list";
		string phyloRabundFile = m->getRootName(m->getSimpleName(fastaTaxFile)) + "tx.rabund";
		
		//clearcut
		thisCommand = "clearcut(phylip=current, neighbor=T)";
		commands.push_back(thisCommand);
		
		string treeFile = m->getRootName(m->getSimpleName(phylipFile)) + "tre";
		
		//read.otu
		thisCommand = "make.shared(list=" + listFile + ", group=" + groupFile + ", label=0.03)";
		commands.push_back(thisCommand);
		
		string sharedFile = m->getRootName(m->getSimpleName(listFile)) + "shared";
		
		//read.otu
		thisCommand = "make.shared(list=" + phyloListFile + ", group=" + groupFile + ", label=1)";
		commands.push_back(thisCommand);
		
		string phyloSharedFile = m->getRootName(m->getSimpleName(phyloListFile)) + "shared";
		
		//read.otu
		thisCommand = "set.current(shared=" + sharedFile + ")";
		commands.push_back(thisCommand);

		//summary.single
		thisCommand = "summary.single(shared=current, calc=nseqs-sobs-coverage-bergerparker-chao-ace-jack-bootstrap-boneh-efron-shen-solow-shannon-npshannon-invsimpson-qstat-simpsoneven-shannoneven-heip-smithwilson, size=5000)";
		commands.push_back(thisCommand);
		
		//summary.shared
		thisCommand = "summary.shared(shared=current, calc=sharednseqs-sharedsobs-sharedchao-sharedace-anderberg-jclass-jest-kulczynski-kulczynskicody-lennon-ochiai-sorclass-sorest-whittaker-braycurtis-jabund-morisitahorn-sorabund-thetan-thetayc)";
		commands.push_back(thisCommand);
		
		//read.otu
		//thisCommand = "read.otu(rabund=" + rabundFile + ", label=0.03)";
		//commands.push_back(thisCommand);
		
		//summary.single
		thisCommand = "summary.single(rabund=" + rabundFile + ", label=0.03, calc=nseqs-sobs-coverage-bergerparker-chao-ace-jack-bootstrap-boneh-efron-shen-solow-shannon-npshannon-invsimpson-qstat-simpsoneven-shannoneven-heip-smithwilson, size=5000)";
		commands.push_back(thisCommand);
		
		//read.otu
		thisCommand = "set.current(shared=" + phyloSharedFile + ")";
		commands.push_back(thisCommand);
		
		//summary.single
		thisCommand = "summary.single(shared=current, calc=nseqs-sobs-coverage-bergerparker-chao-ace-jack-bootstrap-boneh-efron-shen-solow-shannon-npshannon-invsimpson-qstat-simpsoneven-shannoneven-heip-smithwilson, size=5000)";
		commands.push_back(thisCommand);
		
		//summary.shared
		thisCommand = "summary.shared(shared=current, calc=sharednseqs-sharedsobs-sharedchao-sharedace-anderberg-jclass-jest-kulczynski-kulczynskicody-lennon-ochiai-sorclass-sorest-whittaker-braycurtis-jabund-morisitahorn-sorabund-thetan-thetayc)";
		commands.push_back(thisCommand);

		//read.otu
		//thisCommand = "read.otu(rabund=" + phyloRabundFile + ", label=1)";
		//commands.push_back(thisCommand);
		
		//summary.single
		thisCommand = "summary.single(rabund=" + phyloRabundFile + ", label=1, calc=nseqs-sobs-coverage-bergerparker-chao-ace-jack-bootstrap-boneh-efron-shen-solow-shannon-npshannon-invsimpson-qstat-simpsoneven-shannoneven-heip-smithwilson, size=5000)";
		commands.push_back(thisCommand);
		
		//classify.otu
		thisCommand = "classify.otu(taxonomy=" + fastaTaxFile + ", name=" + nameFile + ", list=" + listFile + ", cutoff=51, label=0.03)";
		commands.push_back(thisCommand);
		
		//classify.otu
		thisCommand = "classify.otu(taxonomy=" + fastaTaxFile + ", name=" + nameFile + ", list=" + phyloListFile + ", cutoff=51, label=1)";
		commands.push_back(thisCommand);
		
		//read.tree
		thisCommand = "set.current(tree=" + treeFile + ", name=" + nameFile + ", group=" + groupFile + ")";
		commands.push_back(thisCommand);
		
		//phylo.diversity
		thisCommand = "phylo.diversity(tree=current, group=current, name=current, iters=100,rarefy=T)";
		commands.push_back(thisCommand);
		
		//unifrac.weighted
		thisCommand = "unifrac.weighted(tree=current, group=current, name=current, random=false, distance=true, groups=all, processors=" + toString(processors) + ")";
		commands.push_back(thisCommand);
		
		//unifrac.unweighted
		thisCommand = "unifrac.unweighted(tree=current, group=current, name=current, random=false, distance=true, processors=" + toString(processors) + ")";
		commands.push_back(thisCommand);
		
		
	}
	catch(exception& e) {
		m->errorOut(e, "PipelineCommand", "createPatsPipeline");
		exit(1);
	}
}

//**********************************************************************************************************************