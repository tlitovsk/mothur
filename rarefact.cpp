/*
 *  rarefact.cpp
 *  Dotur
 *
 *  Created by Sarah Westcott on 11/18/08.
 *  Copyright 2008 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "rarefact.h"
//#include "ordervector.hpp"

/***********************************************************************/

int Rarefact::getCurve(float percentFreq = 0.01, int nIters = 1000){
	try {
		RarefactionCurveData* rcd = new RarefactionCurveData();
		for(int i=0;i<displays.size();i++){
			rcd->registerDisplay(displays[i]);
		}
		
		//convert freq percentage to number
		int increment = numSeqs * percentFreq;
		
		for(int iter=0;iter<nIters;iter++){
		
			for(int i=0;i<displays.size();i++){
				displays[i]->init(label);
			}
		
			RAbundVector* lookup	= new RAbundVector(order->getNumBins());
			SAbundVector* rank	= new SAbundVector(order->getMaxRank()+1);
			random_shuffle(order->begin(), order->end());
		
			for(int i=0;i<numSeqs;i++){
			
				if (m->control_pressed) { delete lookup; delete rank; delete rcd; return 0;  }
			
				int binNumber = order->get(i);
				int abundance = lookup->get(binNumber);
			
				rank->set(abundance, rank->get(abundance)-1);
				abundance++;
		
				lookup->set(binNumber, abundance);
				rank->set(abundance, rank->get(abundance)+1);

				if((i == 0) || (i+1) % increment == 0){
					rcd->updateRankData(rank);
				}
			}
	
			if(numSeqs % increment != 0){
				rcd->updateRankData(rank);
			}

			for(int i=0;i<displays.size();i++){
				displays[i]->reset();
			}
			
			delete lookup;
			delete rank;
		}

		for(int i=0;i<displays.size();i++){
			displays[i]->close();
		}
		delete rcd;
		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "Rarefact", "getCurve");
		exit(1);
	}
}

/***********************************************************************/

int Rarefact::getSharedCurve(float percentFreq = 0.01, int nIters = 1000){
try {
		SharedRarefactionCurveData* rcd = new SharedRarefactionCurveData();
		
		label = lookup[0]->getLabel();
		
		//register the displays
		for(int i=0;i<displays.size();i++){
			rcd->registerDisplay(displays[i]);
		}
		
		//if jumble is false all iters will be the same
		if (globaldata->jumble == false)  {  nIters = 1;  }
		
		//convert freq percentage to number
		int increment = numSeqs * percentFreq;
		
		for(int iter=0;iter<nIters;iter++){
		
			for(int i=0;i<displays.size();i++){
				displays[i]->init(label);		  
			}
			
			if (globaldata->jumble == true)  {
				//randomize the groups
				random_shuffle(lookup.begin(), lookup.end());
			}
			
			//make merge the size of lookup[0]
			SharedRAbundVector* merge = new SharedRAbundVector(lookup[0]->size());
			
			//make copy of lookup zero
			for(int i = 0; i<lookup[0]->size(); i++) {
				merge->set(i, lookup[0]->getAbundance(i), "merge");
			}
			
			vector<SharedRAbundVector*> subset;
			//send each group one at a time
			for (int k = 0; k < lookup.size(); k++) { 
				if (m->control_pressed) {  delete merge; delete rcd; return 0;  }
				
				subset.clear(); //clears out old pair of sharedrabunds
				//add in new pair of sharedrabunds
				subset.push_back(merge); subset.push_back(lookup[k]);
				
				rcd->updateSharedData(subset, k+1, numGroupComb);
				mergeVectors(merge, lookup[k]);
			}

			//resets output files
			for(int i=0;i<displays.size();i++){
				displays[i]->reset();
			}
			
			delete merge;
		}
		
		for(int i=0;i<displays.size();i++){
			displays[i]->close();
		}
		
		delete rcd;
		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "Rarefact", "getSharedCurve");
		exit(1);
	}
}

/**************************************************************************************/
void Rarefact::mergeVectors(SharedRAbundVector* shared1, SharedRAbundVector* shared2) {
	try{
		for (int k = 0; k < shared1->size(); k++) {
			//merge new species into shared1
			shared1->set(k, (shared1->getAbundance(k) + shared2->getAbundance(k)), "combo");  //set to 'combo' since this vector now contains multiple groups
		}
	}
	catch(exception& e) {
		m->errorOut(e, "Rarefact", "mergeVectors");
		exit(1);
	}
}

