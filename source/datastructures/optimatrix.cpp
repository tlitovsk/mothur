//
//  optimatrix.cpp
//  Mothur
//
//  Created by Sarah Westcott on 4/20/16.
//  Copyright (c) 2016 Schloss Lab. All rights reserved.
//

#include "optimatrix.h"
#include "progress.hpp"
#include "counttable.h"

/***********************************************************************/

OptiMatrix::OptiMatrix(string d, string df, double c, bool s) : distFile(d), distFormat(df), cutoff(c), sim(s) {
    m = MothurOut::getInstance();
    countfile = ""; namefile = "";
    
    if (distFormat == "phylip") { readPhylip(); }
    else { readColumn();  }
}
/***********************************************************************/
OptiMatrix::OptiMatrix(string d, string nc, string f, string df, double c, bool s) : distFile(d), distFormat(df), format(f), cutoff(c), sim(s) {
    m = MothurOut::getInstance();
    
    if (format == "name") { namefile = nc; countfile = ""; }
    else if (format == "count") { countfile = nc; namefile = ""; }
    else { countfile = ""; namefile = ""; }
    
    if (distFormat == "phylip") { readPhylip(); }
    else { readColumn();  }
}
/***********************************************************************/
int OptiMatrix::readFile(string d, string nc, string f, string df, double c, bool s)  {
    distFile = d; format = f; cutoff = c; sim = s; distFormat = df;
    
    if (format == "name") { namefile = nc; countfile = ""; }
    else if (format == "count") { countfile = nc; namefile = ""; }
    else { countfile = ""; namefile = ""; }
    
    if (distFormat == "phylip") { readPhylip(); }
    else { readColumn();  }
    
    return 0;
}
/***********************************************************************/
ListVector* OptiMatrix::getListSingle() {
    try {
        ListVector* singlelist = NULL;
        
        if (singletons.size() == 0) { }
        else {
            singlelist = new ListVector();
            
            for (int i = 0; i < singletons.size(); i++) {
                string otu = singletons[i];
                singlelist->push_back(otu);
            }
        }
        
        return singlelist;
    }
    catch(exception& e) {
        m->errorOut(e, "OptiMatrix", "getListSingle");
        exit(1);
    }
}
/***********************************************************************/
long int OptiMatrix::print(ostream& out) {
    try {
        long int count = 0;
        for (int i = 0; i < closeness.size(); i++) {
            for(int j=0; j < closeness[i].size();j++){
                out << closeness[i][j] << '\t';
                count++;
            }
            out << endl;
        }
        out << endl;
        return count;
    }
    catch(exception& e) {
        m->errorOut(e, "OptiMatrix", "getName");
        exit(1);
    }
}
/***********************************************************************/
string OptiMatrix::getName(int index) {
    try {
        if (index > closeness.size()) { m->mothurOut("[ERROR]: index is not valid.\n"); m->control_pressed = true; return ""; }
        string name = nameMap[index];
        return name;
    }
    catch(exception& e) {
        m->errorOut(e, "OptiMatrix", "getName");
        exit(1);
    }
}
/***********************************************************************/
//assumes sorted optimatrix
bool OptiMatrix::isClose(int i, int toFind){
    try {
        // Returns index of toFind in sortedArray, or -1 if not found
        int low = 0;
        int high = closeness[i].size() - 1;
        int mid;
        
        int l = closeness[i][low];
        int h = closeness[i][high];
        
        while (l <= toFind && h >= toFind) {
            mid = (low + high)/2;
            
            int m = closeness[i][mid];
            
            if (m < toFind) {
                l = closeness[i][low = mid + 1];
            } else if (m > toFind) {
                h = closeness[i][high = mid - 1];
            } else {
                return true;
            }
        }
        
        if (closeness[i][low] == toFind) {
            return true;
        }else{
            return false; // Not found
        }
    }
    catch(exception& e) {
        m->errorOut(e, "OptiMatrix", "isClose");
        exit(1);
    }
}
/***********************************************************************/

string OptiMatrix::findDistFormat(string distFile){
    try {
        string fileFormat = "column";
        
        ifstream fileHandle;
        string numTest;
        
        m->openInputFile(distFile, fileHandle);
        fileHandle >> numTest;
        fileHandle.close();
        
        if (m->isContainingOnlyDigits(numTest)) { fileFormat = "phylip"; }
        
        return fileFormat;
    }
    catch(exception& e) {
        m->errorOut(e, "OptiMatrix", "findDistFormat");
        exit(1);
    }
}
/***********************************************************************/

int OptiMatrix::readPhylip(){
    try {
        float distance;
        int square, nseqs;
        string name;
        int count = 0;

        ifstream fileHandle;
        string numTest;
        
        m->openInputFile(distFile, fileHandle);
        fileHandle >> numTest >> name;
        
        if (!m->isContainingOnlyDigits(numTest)) { m->mothurOut("[ERROR]: expected a number and got " + numTest + ", quitting."); m->mothurOutEndLine(); exit(1); }
        else { convert(numTest, nseqs); }
        
        vector< map<int, string> > temp; temp.resize(nseqs);
        
        //map shorten name to real name - space saver
        nameMap.push_back(name);
        
        //square test
        char d;
        while((d=fileHandle.get()) != EOF){
            
            if(isalnum(d)){
                square = 1;
                fileHandle.putback(d);
                for(int i=0;i<nseqs;i++){
                    fileHandle >> distance;
                }
                break;
            }
            if(d == '\n'){
                square = 0;
                break;
            }
        }
        
        Progress* reading;
       
        if(square == 0){
            
            reading = new Progress("Reading matrix:     ", nseqs * (nseqs - 1) / 2);
            
            int index = 0;
            
            for(int i=1;i<nseqs;i++){
                if (m->control_pressed) {  fileHandle.close();  delete reading; return 0; }
                
                fileHandle >> name;
                nameMap.push_back(name);
                
                for(int j=0;j<i;j++){
                    
                    if (m->control_pressed) { delete reading; fileHandle.close(); return 0;  }
                    
                    fileHandle >> distance;
                    
                    if (distance == -1) { distance = 1000000; }
                    else if (sim) { distance = 1.0 - distance;  }  //user has entered a sim matrix that we need to convert.
                    
                    if(distance < cutoff){
                        temp[j][i] = name;
                        temp[i][j] = nameMap[j];
                    }
                    index++;
                    reading->update(index);
                }
            }
        }
        else{
            
            reading = new Progress("Reading matrix:     ", nseqs * nseqs);
            
            int index = nseqs;
            
            for(int i=1;i<nseqs;i++){
                fileHandle >> name;
                
                nameMap.push_back(name);
                
                //list->push_back(toString(i));
                
                for(int j=0;j<nseqs;j++){
                    fileHandle >> distance;
                    
                    if (m->control_pressed) {  fileHandle.close();  delete reading; return 0; }
                    
                    if (distance == -1) { distance = 1000000; }
                    else if (sim) { distance = 1.0 - distance;  }  //user has entered a sim matrix that we need to convert.
                    
                    if(distance < cutoff && j < i){
                        temp[j][i] = name;
                        temp[i][j] = nameMap[j];
                    }
                    index++;
                    reading->update(index);
                }
            }
        }
        
        map<string, string> names;
        if (namefile != "") {
            m->readNames(namefile, names);
            //update nameMap
            for (int i = 0; i < nameMap.size(); i++) {
                map<string, string>::iterator it = names.find(nameMap[i]);
                nameMap[i] = it->second;  //we know its there because we read it above
            }
            names.clear();
        }
        
        count = 0;
        map<int, int> closenessIndexMap;
        for (int i = 0; i < temp.size(); i++) {
            //add to singletons +1 singletons count
            if (temp[i].size() == 0) {
                singletons.push_back(nameMap[i]);
            }else {
                int newIndex = closeness.size();
                nameMap[newIndex] = nameMap[i];
                
                vector<int> thisClose;
                for(map<int, string>:: iterator it = temp[i].begin(); it != temp[i].end(); it++) {
                    thisClose.push_back(it->first);
                }
                closeness.push_back(thisClose);
                closenessIndexMap[i] = closeness.size()-1;
            
                temp[i].clear();
            }
        }
        
        for (int i = 0; i < closeness.size(); i++) {
            for (int j = 0; j < closeness[i].size(); j++) {
                closeness[i][j] = closenessIndexMap[closeness[i][j]];
            }
            sort(closeness[i].begin(), closeness[i].end());
        }
        
        if (m->control_pressed) {  fileHandle.close();  delete reading; return 0; }
        
        reading->finish();
        delete reading;
        
        //list->setLabel("0");
        fileHandle.close();
        
        return 0;
        
    }
    catch(exception& e) {
        m->errorOut(e, "OptiMatrix", "readPhylip");
        exit(1);
    }
}
/***********************************************************************/

int OptiMatrix::readColumn(){
    try {
        map<string, int> nameAssignment;
        if (namefile != "") { nameAssignment = m->readNames(namefile); }
        else  {  CountTable ct; ct.readTable(countfile, false, true); nameAssignment = ct.getNameMap(); }
        int count = 0;
        for (map<string, int>::iterator it = nameAssignment.begin(); it!= nameAssignment.end(); it++) {
            it->second = count; count++;
            nameMap.push_back(it->first);
        }
        
        string firstName, secondName;
        float distance;
        map<string, int> indexMap;
        //list = new ListVector();
        
        ifstream fileHandle;
        m->openInputFile(distFile, fileHandle);
        
        vector< map<int, string> > temp; temp.resize(nameAssignment.size());
        
        while(fileHandle){  //let's assume it's a triangular matrix...
            
            fileHandle >> firstName; m->gobble(fileHandle);
            fileHandle >> secondName; m->gobble(fileHandle);
            fileHandle >> distance;	// get the row and column names and distance
            
            if (m->debug) { cout << firstName << '\t' << secondName << '\t' << distance << endl; }
            
            if (m->control_pressed) {  fileHandle.close();   return 0; }
            
            
            
            map<string,int>::iterator itA = nameAssignment.find(firstName);
            map<string,int>::iterator itB = nameAssignment.find(secondName);
            
            if(itA == nameAssignment.end()){  m->mothurOut("AAError: Sequence '" + firstName + "' was not found in the name or count file, please correct\n"); exit(1);  }
            if(itB == nameAssignment.end()){  m->mothurOut("ABError: Sequence '" + secondName + "' was not found in the name or count file, please correct\n"); exit(1);  }
            
            if (distance == -1) { distance = 1000000; }
            else if (sim) { distance = 1.0 - distance;  }  //user has entered a sim matrix that we need to convert.
            
            int indexA = (itA->second);
            int indexB = (itB->second);
            
            if(distance < cutoff){
                temp[indexA][indexB] = secondName;
                temp[indexB][indexA] = firstName;
            }
            
            m->gobble(fileHandle);
        }
        fileHandle.close();
        
        map<string, string> names;
        if (namefile != "") {
            m->readNames(namefile, names);
            //update nameMap
            for (int i = 0; i < nameMap.size(); i++) {
                map<string, string>::iterator it = names.find(nameMap[i]);
                nameMap[i] = it->second;  //we know its there because we read it above
            }
            names.clear();
        }
        
        //nameMap will contain extra indexes and will be larger than closeness.  This should be okay since we don't allow access to nameMap
        map<int, int> closenessIndexMap;
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i].size() == 0) {
                singletons.push_back(nameMap[i]);
            }else {
                string newName = nameMap[i];
                int newIndex = closeness.size();
                nameMap[newIndex] = newName;
                
                vector<int> thisClose;
                for(map<int, string>:: iterator it = temp[i].begin(); it != temp[i].end(); it++) {
                    thisClose.push_back(it->first);
                }
                closeness.push_back(thisClose);
                closenessIndexMap[i] = closeness.size()-1;
                
                temp[i].clear();
            }
        }
        
        for (int i = 0; i < closeness.size(); i++) {
            for (int j = 0; j < closeness[i].size(); j++) {
                closeness[i][j] = closenessIndexMap[closeness[i][j]];
            }
            sort(closeness[i].begin(), closeness[i].end());
        }
        
        if (m->control_pressed) {  fileHandle.close();   return 0; }
        
        fileHandle.close();
        
        //list->setLabel("0");
        
        return 1;
        
    }
    catch(exception& e) {
        m->errorOut(e, "OptiMatrix", "readColumn");
        exit(1);
    }
}
/***********************************************************************/