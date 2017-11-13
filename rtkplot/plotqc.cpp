
#include "rtkplotmain.h"
#include "rtklib.h"
#include "rtkplotopt.h"

void __fastcall TrtkplotMainWindow::ComputeDataIntegrityRate(AnsiString file)
{
	FILE *fp;
	if(!(fp=fopen(file.c_str(),"w"))) return;

	int i,j,k,l,fre;

	if(NObs<=0) {
        Application->MessageBoxA(L"�۲�����Ϊ��",L"��ʾ",MB_OK);
    	return;
	}

	ReadWaitStart();

	quick_sort(Intervals, 0, NObs-1);
	double interval = stacount(Intervals, NObs);

	sortobs1(&Obs);

	char syscodes[]="GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for (i=0;i<Obs.n;i++) {
		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
        int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
            int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
                FcodeVal[iSys][j] = codeval;
            }
		}
	}

	int Tcount[MAXSAT]={0},Acount[MAXSAT]={0},AcountPL[MAXSAT][2*(NFREQ+NEXOBS)]={0},markSys=0;
	int markExist[MAXSAT]={0};
	double avgele = 0.0;
	for(i=0;i<Obs.n;i=j){
		for(j=i;j<Obs.n;j++){
			if(Obs.data[j].sat!=Obs.data[i].sat)
				break;
		}

		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		for (k=0;k<j-i;k++){
			for(l=0;l<NFREQ+NEXOBS;l++){
				if(((int)Obs.data[i+k].P[l])!=0)
					AcountPL[Obs.data[i].sat-1][l*2]+=1;
				if(((int)Obs.data[i+k].L[l])!=0)
					AcountPL[Obs.data[i].sat-1][l*2+1]+=1;
			}
		}

		gtime_t *tempts = (gtime_t*)malloc(sizeof(gtime_t)*(j-i));
		int mark=0;
		tempts[mark++]=Obs.data[i].time;
		for(k=1;k<j-i;k++){
			if(timediff(Obs.data[i+k].time,Obs.data[i+k-1].time)>10*interval){
				tempts[mark++]=Obs.data[i+k-1].time;
				tempts[mark++]=Obs.data[i+k].time;
			}
		}
		tempts[mark++]=Obs.data[j-1].time;
		for(k=0;k<mark;k=k+2){
			Tcount[Obs.data[i].sat-1] +=(int)(timediff(tempts[k+1],tempts[k])/interval)+1;
		}
		free(tempts); tempts=NULL;

		char id[5]; satno2id(Obs.data[i].sat,id);
		int tempPL=0;
		for(k=0;k<2*(NFREQ+NEXOBS);k++){
			if(AcountPL[Obs.data[i].sat-1][k]!=0 && tempPL==0)
				tempPL = AcountPL[Obs.data[i].sat-1][k];
			else{
				if(AcountPL[Obs.data[i].sat-1][k]<tempPL && AcountPL[Obs.data[i].sat-1][k]!=0)
					tempPL = AcountPL[Obs.data[i].sat-1][k];
            }
		}
		Acount[Obs.data[i].sat-1] = tempPL;
		markExist[Obs.data[i].sat-1]= 1;
	}

	char sysstrs[6][4] = {"GPS","GLO","GAL","QZS","SBA","BDS"};
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	int TAPLsum[6][2+2*(NFREQ+NEXOBS)]={0};
	for(i=0;i<MAXSAT;i++){
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p=strchr(syscodes,id[0]);
		j=(int)(p-syscodes);

		TAPLsum[j][0]+=Tcount[i]; TAPLsum[j][1]+=Acount[i];
		for(k=0;k<NFREQ+NEXOBS;k++){
			TAPLsum[j][2+2*k] += AcountPL[i][2*k];
			TAPLsum[j][2+2*k+1] += AcountPL[i][2*k+1];
		}
	}

	sortobs(&Obs);
	fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","Integrity Rate","M (MIXED)","QC VERSION /TYPE");
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c%-4s%-4s",syscodes[i],"TNU","ANU");
		int strlen = 11;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"C%-3s",code2obs(FcodeVal[i][j],&fre));
				fprintf(fp,"L%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 4*2;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		if(TAPLsum[i][0]==0)
			fprintf(fp,"%-10.5f",0.0);
		else
			fprintf(fp,"%-10.5f",(double)TAPLsum[i][1]/(double)TAPLsum[i][0]);
		strlen += 10;
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / SYS_IR");
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(TAPLsum[i][0]==0) {
					fprintf(fp,"%-5.2f%-5.2f",0.0,0.0);
                }
				else {
					fprintf(fp,"%-5.2f%-5.2f",(double)TAPLsum[i][2+2*j]/(double)TAPLsum[i][0],
							(double)TAPLsum[i][2+2*j+1]/(double)TAPLsum[i][0]);
                }
				strlen += 10;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE_IR");
	}
	fprintf(fp,"%-60s%-20s\n",time_str(Obs.data[0].time, 3),"TIME OF FIRST OBS");
	fprintf(fp,"%-60s%-20s\n",time_str(Obs.data[Obs.n-1].time, 3),"TIME OF LAST OBS");
	fprintf(fp,"%-60.3f%-20s\n",interval,"INTERVAL");
	fprintf(fp,"%-60d%-20s\n",NObs,"NUMBER OF EPOCHS");
	fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");

    for(i=0;i<MAXSAT;i++) {
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
        if(!markExist[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		fprintf(fp,"%-5s%-8d%-8d",id,Tcount[i],Acount[i]);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[iSys][j]!=0)
            	fprintf(fp,"%-8d%-8d",AcountPL[i][2*j],AcountPL[i][2*j+1]);
		}
		fprintf(fp,"\n");
    }
	
	fclose(fp);

	ReadWaitEnd();
}

/*void __fastcall TrtkplotMainWindow::ComputeDataIntegrityRate(AnsiString file)
{
	FILE *fp;
	if(!(fp=fopen(file.c_str(),"w"))) return;

	int i,j,k,l,fre;

	if(NObs<=0) {
        Application->MessageBoxA(L"�۲�����Ϊ��",L"��ʾ",MB_OK);
    	return;
    }
	quick_sort(Intervals, 0, NObs-1);
	double interval = stacount(Intervals, NObs);

	fprintf(fp, "%-15s: %s\n", "��ʼ��Ԫʱ��",time_str(Obs.data[0].time, 3));
	fprintf(fp, "%-15s: %s\n","������Ԫʱ��", time_str(Obs.data[Obs.n - 1].time, 3));
	fprintf(fp, "%-15s: %.4f\n","���ü��",interval);
	fprintf(fp, "%-15s: %d\n\n","��Ԫ����",NObs);

	sortobs1(&Obs);

	char syscodes[]="GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for (i=0;i<Obs.n;i++) {
		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
        int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
            int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
                FcodeVal[iSys][j] = codeval;
            }
		}
	}

	int markiSys;
    int Tcount[MAXSAT]={0},Acount[MAXSAT]={0},AcountPL[MAXSAT][2*(NFREQ+NEXOBS)]={0},markSys=0;
	double avgele = 0.0;
	for(i=0;i<Obs.n;i=j){
		for(j=i;j<Obs.n;j++){
			if(Obs.data[j].sat!=Obs.data[i].sat)
				break;
			else
				avgele += Obs.data[j].elevation;
		}
		avgele = avgele/(j-i);

		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		for (k=0;k<j-i;k++){
			for(l=0;l<NFREQ+NEXOBS;l++){
				if(((int)Obs.data[i+k].P[l])!=0)
					AcountPL[Obs.data[i].sat-1][l*2]+=1;
				if(((int)Obs.data[i+k].L[l])!=0)
					AcountPL[Obs.data[i].sat-1][l*2+1]+=1;
			}
		}

		gtime_t *tempts = (gtime_t*)malloc(sizeof(gtime_t)*(j-i));
		int mark=0;
		tempts[mark++]=Obs.data[i].time;
		for(k=1;k<j-i;k++){
			if(timediff(Obs.data[i+k].time,Obs.data[i+k-1].time)>10*interval){
				tempts[mark++]=Obs.data[i+k-1].time;
				tempts[mark++]=Obs.data[i+k].time;
			}
		}
		tempts[mark++]=Obs.data[j-1].time;
		//for(k=0;k<mark;k++){
		//	fprintf(fp,"��ǵ���Ԫ%s\n",time_str(tempts[k],3));
		//}
		for(k=0;k<mark;k=k+2){
			//fprintf(fp,"��Ԫ��%f\n",timediff(tempts[k+1],tempts[k]));
			Tcount[Obs.data[i].sat-1] +=(int)(timediff(tempts[k+1],tempts[k])/interval)+1;
			//fprintf(fp,"%d\n",Tcount[Obs.data[i].sat-1]);
		}
		free(tempts); tempts=NULL;

		if(i==0) {
        	char id[5],*p; satno2id(Obs.data[i].sat,id);
			p = strchr(syscodes,id[0]);
			markiSys = (int)(p-syscodes);
        }
		if(i>1&&(satsys(Obs.data[i].sat,NULL)!=satsys(Obs.data[i-1].sat,NULL))){
			markSys=0;
			char id[5],*p; satno2id(Obs.data[i].sat,id);
			p = strchr(syscodes,id[0]);
			markiSys = (int)(p-syscodes);
			fprintf(fp,"\n");
		}
		if(markSys==0){
			fprintf(fp,"%4s %7s %7s %7s ","SV","#Tsum","<ele>","#Asum");
            int numcode = 0;
			for(k=0;k<NFREQ+NEXOBS;k++){
				if(FcodeVal[markiSys][k]!=0) {
					numcode += 1;
                	fprintf(fp,"%4sC%2s "," ",code2obs(FcodeVal[markiSys][k], &fre));
					fprintf(fp,"%4sL%2s "," ",code2obs(FcodeVal[markiSys][k], &fre));
                }
			}
			fprintf(fp,"\n");
			fprintf(fp,"---- ------- ------- ------- ");
			for(l=0;l<2*numcode;l++)
				fprintf(fp,"------- ");
			fprintf(fp,"\n");
			markSys=1;
		}

		char id[5]; satno2id(Obs.data[i].sat,id);
		fprintf(fp,"%-5s%7d %7.2f ",id,Tcount[Obs.data[i].sat-1],avgele*R2D); int tempPL=0;
		for(k=0;k<2*(NFREQ+NEXOBS);k++){
			if(AcountPL[Obs.data[i].sat-1][k]!=0 && tempPL==0)
				tempPL = AcountPL[Obs.data[i].sat-1][k];
			else{
				if(AcountPL[Obs.data[i].sat-1][k]<tempPL && AcountPL[Obs.data[i].sat-1][k]!=0)
					tempPL = AcountPL[Obs.data[i].sat-1][k];
            }
		}
		Acount[Obs.data[i].sat-1] = tempPL;
        fprintf(fp,"%7d ",tempPL);

		for(k=0;k<NFREQ+NEXOBS;k++){
			if(FcodeVal[markiSys][k]!=0)
				fprintf(fp,"%7d %7d ",AcountPL[Obs.data[i].sat-1][2*k],AcountPL[Obs.data[i].sat-1][2*k+1]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");

	char sysstrs[6][4] = {"GPS","GLO","GAL","QZS","SBA","BDS"};
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	int TAPLsum[6][2+2*(NFREQ+NEXOBS)]={0};
	for(i=0;i<MAXSAT;i++){
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p=strchr(syscodes,id[0]);
		j=(int)(p-syscodes);

		TAPLsum[j][0]+=Tcount[i]; TAPLsum[j][1]+=Acount[i];
		for(k=0;k<NFREQ+NEXOBS;k++){
			TAPLsum[j][2+2*k] += AcountPL[i][2*k];
			TAPLsum[j][2+2*k+1] += AcountPL[i][2*k+1];
		}
	}
	for(i=0;i<6;i++){
		if(!(sysval[i]&NavSys)) continue;

		fprintf(fp,"%-8s",sysstrs[i]);
		if(TAPLsum[i][0]!=0)
			fprintf(fp,"%8.5f",(double)TAPLsum[i][1]/(double)TAPLsum[i][0]);
		else
			fprintf(fp,"%8.2f",0.0);
        fprintf(fp,"%5s%-8d%-8d\n"," ",TAPLsum[i][0],TAPLsum[i][1]);
		for(j=0;j<NFREQ+NEXOBS;j++) {
            if(FcodeVal[i][j]!=0)
				fprintf(fp,"%-8d%-8d",TAPLsum[i][2+2*j],TAPLsum[i][2+2*j+1]);
        }
		fprintf(fp,"\n");
	}

    fclose(fp);
}*/

void __fastcall TrtkplotMainWindow::ComputeMP(AnsiString file)
{
	FILE *fp;
	if(!(fp=fopen(file.c_str(),"w"))) return;
	//char path[1024] = "F:\\Users\\dell\\Desktop\\test.txt";
	//fp = fopen(path,"w");

    ReadWaitStart();

	sortobs(&Obs);
	int i,j,k,fre;
	char syscodes[]="GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	double aMPvals[6][NFREQ+NEXOBS] = {0.0}; int numMPvals[6][NFREQ+NEXOBS] = {0};
	for (i=0;i<Obs.n;i++) {
		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
        int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
            int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
				FcodeVal[iSys][j] = codeval;
				if(fabs(Mp[j][i])>=0.0000000001) {
                	numMPvals[iSys][j] += 1;
					aMPvals[iSys][j] += fabs(Mp[j][i]);
                }
			}
		}
	}

	fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","Multipath Error","M (MIXED)","QC VERSION /TYPE");
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen = 3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 3;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
    for(i=0;i<6;i++) {
    	if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
        int strlen=3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(numMPvals[i][j]==0)
					fprintf(fp,"%-10.5f",0.0);
				else
					fprintf(fp,"%-10.5f",aMPvals[i][j]/numMPvals[i][j]);
				strlen += 10;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / AVE_MP");
    }
	fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");

	for(i=0;i<NObs;i++) {
		fprintf(fp,"%-2s%-27s\n",">",time_str(Obs.data[IndexObs[i]].time,6));
        int jVal = 0;
		if(i==NObs-1)
			jVal = Obs.n;
		else
			jVal = IndexObs[i+1];

		for(j=IndexObs[i];j<jVal;j++) {
			if(!(satsys(Obs.data[j].sat,NULL)&NavSys)) continue;
			if (SatMask[Obs.data[j].sat-1]) continue;
			char id[5],*p; satno2id(Obs.data[j].sat,id);
			fprintf(fp,"%-4s",id);
			p = strchr(syscodes,id[0]);
			int iSys = (int)(p-syscodes);
			for(k=0;k<NFREQ+NEXOBS;k++) {
				if(FcodeVal[iSys][k]!=0)
					fprintf(fp,"%10.5f",Mp[k][j]);
			}
			fprintf(fp,"\n");
		}

	}

	//there are some error in the next.
	/*int i,j,k,l,fre;

	sortobs1(&Obs);

	char syscodes[]="GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for (i=0;i<Obs.n;i++) {
		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
        int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
            int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
                FcodeVal[iSys][j] = codeval;
			}
		}
	}

	int markiSys,markSys=0;
	for(i=0;i<Obs.n;i++) {
		for(j=i;j<Obs.n;j++) {
            if(Obs.data[j].sat != Obs.data[i].sat) break;
		}

		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if(SatMask[Obs.data[i].sat-1]) continue;

		if(i==0) {
			char id[5],*p; satno2id(Obs.data[i].sat,id);
			p = strchr(syscodes,id[0]);
			markiSys = (int)(p-syscodes);
		}
		if(i>1&&(satsys(Obs.data[i].sat,NULL)!=satsys(Obs.data[i-1].sat,NULL))) {
			markSys = 0;
			char id[5],*p; satno2id(Obs.data[i].sat,id);
			p = strchr(syscodes,id[0]);
			markiSys = (int)(p-syscodes);
			fprintf(fp,"\n");
        }

		if(markSys==0) {
			fprintf(fp,"%25s %4s ","Epoch","SV");
			int numcode = 0;
			for(k=0;k<NFREQ+NEXOBS;k++) {
				if(FcodeVal[markiSys][k]!=0) {
					numcode += 1;
					fprintf(fp,"%5s%2s"," ",code2obs(FcodeVal[markiSys][k],&fre));
					fprintf(fp,"-MP%d ",fre);
                }
			}
			fprintf(fp,"\n");
			fprintf(fp,"------------------------- ---- ");
			for(k=0;k<numcode;k++)
				fprintf(fp,"----------- ");
			fprintf(fp,"\n");
			markSys=1;
        }

		for(k=0;k<j-i;k++) {
			//char id[5]; satno2id(Obs.data[i+k].sat,id);
			//fprintf(fp,"%-25s %-4s ",time_str(Obs.data[i+k].time,3),id);
			for(l=0;l<NFREQ+NEXOBS;l++) {
				if(FcodeVal[markiSys][l]!=0)
					fprintf(fp,"%11.5f",Mp[l][i+k]);
			}
			fprintf(fp,"\n");
		}

    }*/

	/*for (i=0;i<Obs.n;i++) {
		char id[5]; satno2id(Obs.data[i].sat, id);
		fprintf(fp,"%-25s%-4s",time_str(Obs.data[i].time,3),id);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[j]!=0)
				fprintf(fp,"%10.5f",Mp[j][i]);
		}
		fprintf(fp,"\n");
	}*/

	fclose(fp);

	ReadWaitEnd();
}

void __fastcall TrtkplotMainWindow::ComputeCNR(AnsiString file)
{
	FILE *fp;
	if(!(fp=fopen(file.c_str(),"w"))) return;
	//char path[1024] = "F:\\Users\\dell\\Desktop\\test.txt";
	//fp = fopen(path,"w");

	ReadWaitStart();

	sortobs(&Obs);
	int i,j,k,fre;
	char syscodes[] = "GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	double aCNRvals[6][NFREQ+NEXOBS] = {0.0}; int numCNRvals[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			int codeval = (int)Obs.data[i].code[j];
			if(codeval!=0) {
				FcodeVal[iSys][j] = codeval;
				if(Obs.data[i].SNR[j] >0.0) {
					numCNRvals[iSys][j] += 1;
					aCNRvals[iSys][j] += Obs.data[i].SNR[j]*0.25;
                }
            }
        }
	}

    fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","CNR Value","M (MIXED)","QC VERSION /TYPE");
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen = 3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 3;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
	for(i=0;i<6;i++){
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen = 3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(numCNRvals[i][j]==0)
					fprintf(fp,"%-10.5f",0.0);
				else
					fprintf(fp,"%-10.5f",aCNRvals[i][j]/numCNRvals[i][j]);
				strlen += 10;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / AVE_CNR");	
	}
	fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");

	for(i=0;i<NObs;i++) {
    	fprintf(fp,"%-2s%-27s\n",">",time_str(Obs.data[IndexObs[i]].time,6));
        int jVal = 0;
		if(i==NObs-1)
			jVal = Obs.n;
		else
			jVal = IndexObs[i+1];

		for(j=IndexObs[i];j<jVal;j++) {
        	if(!(satsys(Obs.data[j].sat,NULL)&NavSys)) continue;
			if (SatMask[Obs.data[j].sat-1]) continue;
			char id[5],*p; satno2id(Obs.data[j].sat,id);
			fprintf(fp,"%-4s",id);
			p = strchr(syscodes,id[0]);
			int iSys = (int)(p-syscodes);
			for(k=0;k<NFREQ+NEXOBS;k++) {
				if(FcodeVal[iSys][k]!=0)
					fprintf(fp,"%10.5f",Obs.data[j].SNR[k]*0.25);
			}
			fprintf(fp,"\n");
        }
    }

	/*int i;
	for(i=0;i<Obs.n;i++){
		char id[5]; satno2id(Obs.data[i].sat, id);
		fprintf(fp,"%-25s%-4s%10.5f%10.5f%10.5f\n",time_str(Obs.data[i].time,3),id,Obs.data[i].SNR[0]*0.25,
				Obs.data[i].SNR[1]*0.25,Obs.data[i].SNR[2]*0.25);
	}*/

	fclose(fp);

	ReadWaitEnd();
}

static void diffArray(double *vals,int n,double *revals)
{
	int i;
	for(i=0;i<n-1;i++){
    	revals[i] = vals[i+1]-vals[i];
	}
}
static double compueMdiff(double *vals,int n,int mark)
{
	double *revals = (double*)malloc(sizeof(double)*n),sum=0;
	double *tempvals = (double*)malloc(sizeof(double)*n),average,varL;
	int i,j,count=0;
	for(i=0;i<mark;i++){
		diffArray(vals,n-i,revals);
		for(j=0;j<n-i-1;j++)
			vals[j]=revals[j];
		free(revals);
		revals = (double*)malloc(sizeof(double)*n);
	}

	for(i=0;i<n-mark;i++){
		if(fabs(vals[i])<0.1){               ///////////////////
			tempvals[count++]=fabs(vals[i]);
            sum += fabs(vals[i]);
		}
	}
	if(count==0)
		average = 0.0;
	else
		average = sum/count; 
	sum=0.0;
	for(i=0;i<count;i++){
        sum+=(tempvals[i]-average)*(tempvals[i]-average);
	}
	if(count<=1)
		varL = 0.0;
	else
		varL = sqrt(sum/(count-1));
	varL = varL/sqrt(8.0);

    free(revals); free(tempvals); revals=NULL; tempvals=NULL;
    return varL;
}

void __fastcall TrtkplotMainWindow::ComputeCn(AnsiString file)
{
	FILE *fp;
	if(!(fp=fopen(file.c_str(),"w"))) return;
	//char path[1024] = "F:\\Users\\dell\\Desktop\\test.txt";
	//fp = fopen(path,"w");

	ReadWaitStart();

	sortobs1(&Obs);
	int i,j,k,l,fre; char syscodes[] = "GREJSC";
	double Cns[MAXSAT][NFREQ+NEXOBS] = {0}; int markExist[MAXSAT]={0};
	double aCnvals[6][NFREQ+NEXOBS] = {0.0}; int numCnvals[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i=j){
		for(j=i;j<Obs.n;j++){
            if(Obs.data[j].sat!=Obs.data[i].sat) break;
		}
        if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		char id[5],*p; satno2id(Obs.data[i].sat, id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		//fprintf(fp,"%-5s",id);
		for(l=0;l<NFREQ+NEXOBS;l++){
            double *Ls = (double*)malloc(sizeof(double)*(j-i));
			for(k=0;k<j-i;k++){
				//if(Obs.data[i+k].L[l]>0.0)
				Ls[k]=Obs.data[i+k].L[l];
			}
			Cns[Obs.data[i].sat-1][l] = compueMdiff(Ls,j-i,3);
			markExist[Obs.data[i].sat-1] = 1;

			if(Cns[Obs.data[i].sat-1][l]>0.0) {
				aCnvals[iSys][l] += Cns[Obs.data[i].sat-1][l];
				numCnvals[iSys][l] += 1;
			}
			//fprintf(fp,"%-10.5f",Cns[Obs.data[i].sat-1][l]);
		}
		//fprintf(fp,"\n");
	}

	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			int codeval = (int)Obs.data[i].code[j];
			if(codeval!=0) {
				FcodeVal[iSys][j] = codeval;
            }
        }
	}
	fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","Cn Value","M (MIXED)","QC VERSION /TYPE");
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen = 3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 3;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
	for(i=0;i<6;i++) {
    	if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen = 3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(numCnvals[i][j]==0)
					fprintf(fp,"%-10.5f",0.0);
				else 
					fprintf(fp,"%-10.5f",aCnvals[i][j]/numCnvals[i][j]);
				strlen += 10;
            }
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / AVE_Cn");
    }
	fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");

	for(i=0;i<MAXSAT;i++) {
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
        if(!markExist[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		fprintf(fp,"%-5s",id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[iSys][j]!=0)
            	fprintf(fp,"%-10.5f",Cns[i][j]);
		}
		fprintf(fp,"\n");
    }

	fclose(fp);

	ReadWaitEnd();
}

static double* TPval(double *gx,double *x,int count,int m)
{
	double *dx_gf = (double*)malloc(sizeof(double)*count);
	int i,j;
	for(i=0;i<count;i++){
		//dx_gf[i]=gx[i]- (i*i*x[0]+i*x[1]+x[2]);
		dx_gf[i]=0;
		for(j=0;j<m;j++){
			if(i==0&&(m-j-1==0))
				dx_gf[i]+=x[j];
			else
            	dx_gf[i]+=pow(i,m-j-1)*x[j];
		}
        dx_gf[i] = gx[i]-dx_gf[i];
	}
	return dx_gf;
}

static double ployFitPn(double *vals,int n,int m)
{
	double THRES_Pn = 0.1;
	double *redvals = (double*)malloc(sizeof(double)*n);int re_c=0;
	double *temp120 = (double*)malloc(sizeof(double)*120);
	int i=0,j,k,index=0;
	while(i<n){
		if(index<120){
            temp120[index++]=vals[i];
		}
		else if(index==120){
			double *x=(double*)malloc(sizeof(double)*m),*Q=(double*)malloc(sizeof(double)*m*m); Q=eye(m);
			double *A = (double*)malloc(sizeof(double)*120*m),*dx_gf;
			for(j=0;j<120;j++){
				for(k=0;k<m;k++){
					if(j==0&&(m-k-1==0))
						A[m*j+k]=1;
					else
						A[m*j+k]=pow(j,m-k-1);
				}
				//A[3*j] = j*j;A[3*j+1]=j;A[3*j+2]=1;
			}
			if(lsq(A,temp120,m,120,x,Q)!=0)
				return 0;
            dx_gf=TPval(temp120,x,120,m);
			for(j=0;j<120;j++){
				if(fabs(dx_gf[j])<THRES_Pn)
                	redvals[re_c++]=dx_gf[j];
			}

			free(Q); free(A); Q=NULL; A=NULL;
			free(temp120);temp120 = (double*)malloc(sizeof(double)*120);
            index=0;
		}
		i++;
	}
	if(index>=3&&index<=120){
		double *x=(double*)malloc(sizeof(double)*m),*Q=(double*)malloc(sizeof(double)*m*m); Q=eye(m);
		double *A = (double*)malloc(sizeof(double)*120*m),*dx_gf;
		for(j=0;j<index;j++){
			for(k=0;k<m;k++)
				if(j==0&&(m-k-1==0))
					A[m*j+k]=1;
				else
					A[m*j+k]=pow(j,m-k-1);
			//A[3*j] = j*j;A[3*j+1]=j;A[3*j+2]=1;
		}
		if(lsq(A,temp120,m,index,x,Q)!=0)
			return 0;
		dx_gf=TPval(temp120,x,index,m);
		for(j=0;j<index;j++){
			if(fabs(dx_gf[j])<THRES_Pn)
				redvals[re_c++]=dx_gf[j];
		}

		free(Q);free(A);Q=NULL;A=NULL;
		free(temp120); temp120=NULL;
	}

	double sum=0;
	for(i=0;i<re_c;i++){
        sum += fabs(redvals[i]);
	}

	free(redvals); redvals=NULL;
	if(re_c==0)
		return 0;

	return sum/re_c;
}

static double* ployFilPnAll(double *vals,int n)
{
	int i;
	double x[3]={0},*Q=(double*)malloc(sizeof(double)*9); Q=eye(3);
	double *A=(double*)malloc(sizeof(double)*n*3);
	for(i=0;i<n;i++){
		A[3*i]=i*i;A[3*i+1]=i;A[3*i+2]=1;
	}
	lsq(A,vals,3,n,x,Q);

    free(Q);free(A); Q=NULL;A=NULL;
    double *dx_gf = (double*)malloc(sizeof(double)*n);
	for(i=0;i<n;i++){
		dx_gf[i]=vals[i]- (i*i*x[0]+i*x[1]+x[2]);
	}
    return dx_gf;
}

void __fastcall TrtkplotMainWindow::ComputePn(AnsiString file)
{
	FILE *fp;
	if(!(fp=fopen(file.c_str(),"w"))) return;
	//char path[1024] = "F:\\Users\\dell\\Desktop\\test.txt";
	//fp = fopen(path,"w");

    ReadWaitStart();

	quick_sort(Intervals, 0, NObs-1);
	double interval = stacount(Intervals, NObs);

	sortobs1(&Obs);
	int i,j,k,l,m,fre;  char syscodes[] = "GREJSC";
	double Pns[MAXSAT][NFREQ+NEXOBS] = {0}; int markExist[MAXSAT] = {0};
	double aPnvals[6][NFREQ+NEXOBS] = {0.0}; int numPnvals[6][NFREQ+NEXOBS]={0};
    for(i=0;i<Obs.n;i=j){
		for(j=i;j<Obs.n;j++){
            if(Obs.data[j].sat!=Obs.data[i].sat) break;
		}
        if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		int *indexs = (int*)malloc(sizeof(int)*(j-i));
		int i_count=0;
		indexs[i_count++]=i;
		for(k=1;k<j-i;k++){
			if(timediff(Obs.data[i+k].time,Obs.data[i+k-1].time)>10*interval){
				indexs[i_count++]=i+k-1;
				indexs[i_count++]=i+k;
			}
		}
		indexs[i_count++]=j-1;

		//for(k=0;k<i_count;k++){
		//	fprintf(fp,"%10d",indexs[k]);
		//}

		char id[5],*p; satno2id(Obs.data[i].sat, id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		//fprintf(fp,"%-5s",id);
		for(l=0;l<NFREQ+NEXOBS;l++){
			double tempsum =0;
			for(k=0;k<i_count;k=k+2){
				double *Ps=(double*)malloc(sizeof(double)*(indexs[k+1]-indexs[k]+1));
				int Ps_count=0;
				for(m=indexs[k];m<=indexs[k+1];m++){
					if((int)(Obs.data[m].P[l])!=0)
						Ps[Ps_count++]=Obs.data[m].P[l];
				}
				//revals = ployFitPn(Ps,Ps_count,10,re_count); //order=10
				//revals = ployFilPnAll(Ps,Ps_count);
				if(Ps_count>=10)
					tempsum += ployFitPn(Ps,Ps_count,10);

				free(Ps); Ps=NULL;
			}

			Pns[Obs.data[i].sat-1][l] = tempsum/(i_count/2);
			markExist[Obs.data[i].sat-1] = 1;

			if(Pns[Obs.data[i].sat-1][l]>0.0) {
				aPnvals[iSys][l] += Pns[Obs.data[i].sat-1][l];
				numPnvals[iSys][l] += 1;
            }
            //fprintf(fp,"%-10.5f",tempsum/(i_count/2));
		}

		//fprintf(fp,"\n");
	}

	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			int codeval = (int)Obs.data[i].code[j];
			if(codeval!=0) {
				FcodeVal[iSys][j] = codeval;
            }
        }
	}

	fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","Pn Value","M (MIXED)","QC VERSION /TYPE");
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
    for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen = 3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 3;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
	for(i=0;i<6;i++) {
    	if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen = 3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(numPnvals[i][j]==0)
					fprintf(fp,"%-10.5f",0.0);
				else 
					fprintf(fp,"%-10.5f",aPnvals[i][j]/numPnvals[i][j]);
				strlen += 10;
            }
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / AVE_Pn");
    }
	fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");

	for(i=0;i<MAXSAT;i++) {
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
        if(!markExist[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		fprintf(fp,"%-5s",id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[iSys][j]!=0)
            	fprintf(fp,"%-10.5f",Pns[i][j]);
		}
		fprintf(fp,"\n");
    }
	
	fclose(fp);

	ReadWaitEnd();
}

void __fastcall TrtkplotMainWindow::ComputeObservationPerSlip(AnsiString file)
{
	FILE *fp;
	//AnsiString file = "F:\\Users\\dell\\Desktop\\test.txt";
	if(!(fp=fopen(file.c_str(),"w"))) return;

	ReadWaitStart();

	sortobs(&Obs);

	int i,j,k,l,fre;
	char syscodes[] = "GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
            int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
                FcodeVal[iSys][j] = codeval;
            }
		}
	}

	sortobs1(&Obs);  //Ϊ�˼���������

	int Acount[MAXSAT]={0},AcountL[MAXSAT][NFREQ+NEXOBS]={0},
		markExist[MAXSAT]={0},TALsum[6][1+NFREQ+NEXOBS]={0};
	for(i=0;i<Obs.n;i=j) {
		for(j=i;j<Obs.n;j++) {
        	if(Obs.data[j].sat!=Obs.data[i].sat) break;    
		}

		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		for(k=0;k<j-i;k++) {
			for(l=0;l<NFREQ+NEXOBS;l++) 
				if(((int)Obs.data[i+k].L[l])!=0)
					AcountL[Obs.data[i].sat-1][l]+=1;
		}

		int tempL=0;
		for(k=0;k<NFREQ+NEXOBS;k++) {
			if(AcountL[Obs.data[i].sat-1][k]!=0 && tempL==0)
				tempL = AcountL[Obs.data[i].sat-1][k];
			else {
				if(AcountL[Obs.data[i].sat-1][k]<tempL && AcountL[Obs.data[i].sat-1][k]!=0)
					tempL = AcountL[Obs.data[i].sat-1][k];
            }
        }

		Acount[Obs.data[i].sat-1]=tempL; markExist[Obs.data[i].sat-1]=1;
	}

	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p=strchr(syscodes,id[0]);
		j=(int)(p-syscodes);

		TALsum[j][0]+=Acount[i];
		for(k=0;k<NFREQ+NEXOBS;k++) 
			TALsum[j][1+k] += AcountL[i][k];    
    }

	///////////////////////////////////////////////////////////////////////////////////////////
    sortobs(&Obs);   //Ϊ�˼�����������

	//count the number cycle slip  by CycleSlipMark[NFREQ+NEXOBS][Obs.n]
	int SlipAcount[MAXSAT]={0},SlipAcountL[MAXSAT][NFREQ+NEXOBS]={0},SlipTALsum[6][1+NFREQ+NEXOBS]={0};
	for(i=0;i<Obs.n;i++) {
		//if(El[i]*R2D>0 && El[i]*R2D<10) continue;  //�����˵�Obs�Ѿ����Ź���ģ����Բ��У���ע��
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(CycleSlipMark[j][i]==1) {
                SlipAcountL[Obs.data[i].sat-1][j]+=1;
            }
        }
	}
	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		if(!markExist[i]) continue;

		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		
		int tempSlipL = SlipAcountL[i][0];
		for(j=0;j<NFREQ+NEXOBS;j++) {    
			SlipTALsum[iSys][1+j] += SlipAcountL[i][j];
			if(SlipAcountL[i][j]>tempSlipL)
				tempSlipL = SlipAcountL[i][j];
		}
		SlipAcount[i] = tempSlipL;
	}
	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		if(!markExist[i]) continue;

		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		SlipTALsum[iSys][0] += SlipAcount[i];
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	
    int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","O/Slps","M (MIXED)","QC VERSION /TYPE");
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c%-4s",syscodes[i],"ANU");
		int strlen = 7;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"L%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 4;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		if(SlipTALsum[i][0]==0)
			fprintf(fp,"%-10.0f",(double)TALsum[i][0]);
		else
			fprintf(fp,"%-10.0f",(double)TALsum[i][0]/(double)SlipTALsum[i][0]);
		strlen += 10;
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / SYS_O/Slps");  
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(SlipTALsum[i][1+j]==0) {
					fprintf(fp,"%-10.0f",(double)TALsum[i][1+j]);
					//fprintf(fp,"%-10.0f%-10.0f",(double)TALsum[i][1+j],0);
				}
				else {
					fprintf(fp,"%-10.0f",(double)TALsum[i][1+j]/(double)SlipTALsum[i][1+j]);
					//fprintf(fp,"%-10.0f%-10.0f",(double)TALsum[i][1+j],(double)SlipTALsum[i][1+j]);
				}
				strlen += 10;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE_O/Slps");
	}
	fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");

	for(i=0;i<MAXSAT;i++) {
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
        if(!markExist[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		if(SlipAcount[i]==0)
			//fprintf(fp,"%-5s%-8d%-8d",id,Acount[i],0);
			fprintf(fp,"%-5s%-8d",id,Acount[i]);
		else {
			//fprintf(fp,"%-5s%-8d%-8d",id,Acount[i],SlipAcount[i]);
			fprintf(fp,"%-5s%-8d",id,Acount[i]/SlipAcount[i]);  //������
        }
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[iSys][j]!=0) {
				if(SlipAcountL[i][j]==0)
					//fprintf(fp,"%-8d%-8d",AcountL[i][j],0);
					fprintf(fp,"%-8d",AcountL[i][j]);
				else {
					if(AcountL[i][j]==0)
						fprintf(fp,"%-8d",AcountL[i][j]);
						//fprintf(fp,"%-8d%-8d",AcountL[i][j],0);
					else
						//fprintf(fp,"%-8d%-8d",AcountL[i][j],SlipAcountL[i][j]);
						fprintf(fp,"%-8d",AcountL[i][j]/SlipAcountL[i][j]);  //������
                }
            }
		}
		fprintf(fp,"\n");
    }
	
	fclose(fp);

	ReadWaitEnd();
}

void __fastcall TrtkplotMainWindow::ComputeSlip(AnsiString file)
{
	FILE *fp;
	//AnsiString file = "F:\\Users\\dell\\Desktop\\test.txt";
	if(!(fp=fopen(file.c_str(),"w"))) return;

    ReadWaitStart();

	sortobs(&Obs);
	int i,j,fre;
	char syscodes[] = "GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0},markExist[MAXSAT]={0};
	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		markExist[Obs.data[i].sat-1]=1;
		int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
            int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
                FcodeVal[iSys][j] = codeval;
            }
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	//detect cycle slip
	int SlipAcount[MAXSAT]={0},SlipAcountL[MAXSAT][NFREQ+NEXOBS]={0},SlipTALsum[6][1+NFREQ+NEXOBS]={0};

	//detect cycle slip by LLI (UpdateMp)
	//detect cycle slip by multipath jump (UpdateMp)
	//detect cycle slip by geometry free phase jump (UpdateCycleSlipMark)
	for(i=0;i<Obs.n;i++) {
		//if(El[i]*R2D>0 && El[i]*R2D <10) continue; //��������Obs�Ѿ����Ź���ģ����У���ע��
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(CycleSlipMark[j][i]==1) {
                SlipAcountL[Obs.data[i].sat-1][j]+=1;
            }
        }
	}
	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		if(!markExist[i]) continue;

		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		
		int tempSlipL = SlipAcountL[i][0];
		for(j=0;j<NFREQ+NEXOBS;j++) {    
			SlipTALsum[iSys][1+j] += SlipAcountL[i][j];
			if(SlipAcountL[i][j]>tempSlipL)
				tempSlipL = SlipAcountL[i][j];
		}
		SlipAcount[i] = tempSlipL;
	}
	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		if(!markExist[i]) continue;

		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		SlipTALsum[iSys][0] += SlipAcount[i];
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	
    int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","Slps","M (MIXED)","QC VERSION /TYPE");
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c%-4s",syscodes[i],"ANU");
		int strlen = 7;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"L%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 4;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		//if(TALsum[i][0]==0)
		//	fprintf(fp,"%-10.5f",0.0);
		//else
		//	fprintf(fp,"%-10.5f",(double)TAPLsum[i][1]/(double)TAPLsum[i][0]);
		fprintf(fp,"%-10.0f",(double)SlipTALsum[i][0]);
		strlen += 10;
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / SYS_Slps");  
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				//if(TAPLsum[i][0]==0) {
				//	fprintf(fp,"%-5.2f%-5.2f",0.0,0.0);
				//}
				//else {
				// 	fprintf(fp,"%-5.2f%-5.2f",(double)TAPLsum[i][2+2*j]/(double)TAPLsum[i][0],
				//			(double)TAPLsum[i][2+2*j+1]/(double)TAPLsum[i][0]);
				//}
				fprintf(fp,"%-10.0f",(double)SlipTALsum[i][1+j]);
				strlen += 10;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE_Slps");
	}
	fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");

	for(i=0;i<MAXSAT;i++) {
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
        if(!markExist[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		fprintf(fp,"%-5s%-8d",id,SlipAcount[i]);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[iSys][j]!=0)
            	fprintf(fp,"%-8d",SlipAcountL[i][j]);
		}
		fprintf(fp,"\n");
    }
	
	fclose(fp);

	ReadWaitEnd();
}

void __fastcall TrtkplotMainWindow::ComputeIon(AnsiString file)
{
	FILE *fp;
	//AnsiString file = "F:\\Users\\dell\\Desktop\\test.txt";
	if(!(fp=fopen(file.c_str(),"w"))) return;

	ReadWaitStart();

    sortobs(&Obs);

	int i,j,k,fre,sat;
	char syscodes[] = "GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS]={0};
	double *Iod[NFREQ+NEXOBS];
    for(i=0;i<NFREQ+NEXOBS;i++) {
		Iod[i] = new double[Obs.n];
	}

	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys=(int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			Iod[j][i]=0.0;
			int codeval=(int)Obs.data[i].code[j];
			if(codeval!=0)
				FcodeVal[iSys][j] = codeval;
        }
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//compute derivative of ionospheric delay
    int numIod[6][NFREQ+NEXOBS] ={0};

	for(sat=7;sat<=MAXSAT;sat++) {
        if(!(satsys(sat,NULL)&NavSys)) continue;
		if (SatMask[sat-1]) continue;
		char id[5],*p; satno2id(sat,id);
		p = strchr(syscodes,id[0]);
		int iSys=(int)(p-syscodes);

		for(i=0;i<NFREQ+NEXOBS;i++) {
            if(FcodeVal[iSys][i]==0) continue;
            double ion0=0,ion1=0;gtime_t t0={0},t1={0};
			for(j=0;j<Obs.n;j++) {
				if(Obs.data[j].sat!=sat) continue;

				ion0=ion1; t0=t1;
				ion1 = Ion[i][j]; t1=Obs.data[j].time;

				//if(Obs.data[0].time.time==t0.time&&Obs.data[0].time.sec==t0.sec) continue;
                if(t0.time==0 && t0.sec<0.00000001) continue;

				Iod[i][j]=100*(ion1-ion0)/(timediff(t1,t0)/60);

				if(Iod[i][j]>400) {
                    numIod[iSys][i] += 1;
                }
			}

        }
    }

	/////////////////////////////////////////////////////////////////////////////////////////////////////

    fprintf(fp,"%9.2f%-11s%-20s%-20s%-20s\n",1.0,"","Ionospheric Effect","M (MIXED)","QC VERSION /TYPE");
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				fprintf(fp,"%-3s",code2obs(FcodeVal[i][j],&fre));
				strlen += 3;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","SYS / # / FRE TYPES");
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		fprintf(fp,"%-3c",syscodes[i]);
		int strlen=3;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
            	fprintf(fp,"%-5d",numIod[i][j]);
				strlen += 5;
			}
		}
		fprintf(fp,"%*.s%-20s\n",60-strlen,"","IODslip(>400cm/min)");
    }
    fprintf(fp,"%-60.60s%-20s\n","","END OF HEADER");


	for(i=0;i<NObs;i++) {
    	fprintf(fp,"%-2s%-27s\n",">",time_str(Obs.data[IndexObs[i]].time,6));
        int jVal = 0;
		if(i==NObs-1)
			jVal = Obs.n;
		else
			jVal = IndexObs[i+1];

		for(j=IndexObs[i];j<jVal;j++) {
        	if(!(satsys(Obs.data[j].sat,NULL)&NavSys)) continue;
			if (SatMask[Obs.data[j].sat-1]) continue;
			char id[5],*p; satno2id(Obs.data[j].sat,id);
			p = strchr(syscodes,id[0]);
			int iSys = (int)(p-syscodes);

			fprintf(fp,"i%-4s",id);
			for(k=0;k<NFREQ+NEXOBS;k++) {
				if(FcodeVal[iSys][k]!=0)
					fprintf(fp,"%10.5f",Ion[k][j]);
			}
			fprintf(fp,"\n");

			fprintf(fp,"d%-4s",id);
			for(k=0;k<NFREQ+NEXOBS;k++) {
            	if(FcodeVal[iSys][k]!=0)
					fprintf(fp,"%10.5f",Iod[k][j]);
			}
			fprintf(fp,"\n");
        }
    }

	fclose(fp);

	ReadWaitEnd();
}

void __fastcall TrtkplotMainWindow::s_ComputeDataIntergirtyRate(int FcodeVal[][NFREQ+NEXOBS])
{
	int i,j,k,l,fre;
	char syscodes[]="GREJSC";

	quick_sort(Intervals, 0, NObs-1);
	double interval = stacount(Intervals, NObs);

	sortobs1(&Obs);

	int Tcount[MAXSAT]={0},Acount[MAXSAT]={0},AcountPL[MAXSAT][2*(NFREQ+NEXOBS)]={0},markSys=0;
	int markExist[MAXSAT]={0};
	double avgele = 0.0;
	for(i=0;i<Obs.n;i=j){
		for(j=i;j<Obs.n;j++){
			if(Obs.data[j].sat!=Obs.data[i].sat)
				break;
		}

		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		for (k=0;k<j-i;k++){
			for(l=0;l<NFREQ+NEXOBS;l++){
				if(((int)Obs.data[i+k].P[l])!=0)
					AcountPL[Obs.data[i].sat-1][l*2]+=1;
				if(((int)Obs.data[i+k].L[l])!=0)
					AcountPL[Obs.data[i].sat-1][l*2+1]+=1;
			}
		}

		gtime_t *tempts = (gtime_t*)malloc(sizeof(gtime_t)*(j-i));
		int mark=0;
		tempts[mark++]=Obs.data[i].time;
		for(k=1;k<j-i;k++){
			if(timediff(Obs.data[i+k].time,Obs.data[i+k-1].time)>10*interval){
				tempts[mark++]=Obs.data[i+k-1].time;
				tempts[mark++]=Obs.data[i+k].time;
			}
		}
		tempts[mark++]=Obs.data[j-1].time;
		for(k=0;k<mark;k=k+2){
			Tcount[Obs.data[i].sat-1] +=(int)(timediff(tempts[k+1],tempts[k])/interval)+1;
		}
		free(tempts); tempts=NULL;

		char id[5]; satno2id(Obs.data[i].sat,id);
		int tempPL=0;
		for(k=0;k<2*(NFREQ+NEXOBS);k++){
			if(AcountPL[Obs.data[i].sat-1][k]!=0 && tempPL==0)
				tempPL = AcountPL[Obs.data[i].sat-1][k];
			else{
				if(AcountPL[Obs.data[i].sat-1][k]<tempPL && AcountPL[Obs.data[i].sat-1][k]!=0)
					tempPL = AcountPL[Obs.data[i].sat-1][k];
            }
		}
		Acount[Obs.data[i].sat-1] = tempPL;
		markExist[Obs.data[i].sat-1]= 1;
	}

	char sysstrs[6][4] = {"GPS","GLO","GAL","QZS","SBA","BDS"};
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	int TAPLsum[6][2+2*(NFREQ+NEXOBS)]={0};
	for(i=0;i<MAXSAT;i++){
		if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p=strchr(syscodes,id[0]);
		j=(int)(p-syscodes);

		TAPLsum[j][0]+=Tcount[i]; TAPLsum[j][1]+=Acount[i];
		for(k=0;k<NFREQ+NEXOBS;k++){
			TAPLsum[j][2+2*k] += AcountPL[i][2*k];
			TAPLsum[j][2+2*k+1] += AcountPL[i][2*k+1];
		}
	}

	sortobs(&Obs);

	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		if(TAPLsum[i][0]==0)
			summaryVal_sys[i][0]=0.0;
		else
			summaryVal_sys[i][0]= (double)TAPLsum[i][1]/(double)TAPLsum[i][0];
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(TAPLsum[i][0]==0) {
                    summaryVal[i][j][0]=0.0;
                }
				else {
					double pI = (double)TAPLsum[i][2+2*j]/(double)TAPLsum[i][0];
					double lI = (double)TAPLsum[i][2+2*j+1]/(double)TAPLsum[i][0];
					summaryVal[i][j][0]=(pI+lI)/2.0;
                }
			}
		}

	}

}

void __fastcall TrtkplotMainWindow::s_ComputeObservationPerSlip(int FcodeVal[][NFREQ+NEXOBS])
{
	sortobs(&Obs);

	int i,j,k,l,fre;
	char syscodes[] = "GREJSC";

	sortobs1(&Obs);  //Ϊ�˼���������

	int Acount[MAXSAT]={0},AcountL[MAXSAT][NFREQ+NEXOBS]={0},
		markExist[MAXSAT]={0},TALsum[6][1+NFREQ+NEXOBS]={0};
	for(i=0;i<Obs.n;i=j) {
		for(j=i;j<Obs.n;j++) {
        	if(Obs.data[j].sat!=Obs.data[i].sat) break;
		}

		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		for(k=0;k<j-i;k++) {
			for(l=0;l<NFREQ+NEXOBS;l++)
				if(((int)Obs.data[i+k].L[l])!=0)
					AcountL[Obs.data[i].sat-1][l]+=1;
		}

		int tempL=0;
		for(k=0;k<NFREQ+NEXOBS;k++) {
			if(AcountL[Obs.data[i].sat-1][k]!=0 && tempL==0)
				tempL = AcountL[Obs.data[i].sat-1][k];
			else {
				if(AcountL[Obs.data[i].sat-1][k]<tempL && AcountL[Obs.data[i].sat-1][k]!=0)
					tempL = AcountL[Obs.data[i].sat-1][k];
            }
        }

		Acount[Obs.data[i].sat-1]=tempL; markExist[Obs.data[i].sat-1]=1;
	}

	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		char id[5],*p; satno2id(i+1,id);
		p=strchr(syscodes,id[0]);
		j=(int)(p-syscodes);

		TALsum[j][0]+=Acount[i];
		for(k=0;k<NFREQ+NEXOBS;k++)
			TALsum[j][1+k] += AcountL[i][k];
    }

	///////////////////////////////////////////////////////////////////////////////////////////
    sortobs(&Obs);   //Ϊ�˼�����������

	//count the number cycle slip  by CycleSlipMark[NFREQ+NEXOBS][Obs.n]
	int SlipAcount[MAXSAT]={0},SlipAcountL[MAXSAT][NFREQ+NEXOBS]={0},SlipTALsum[6][1+NFREQ+NEXOBS]={0};
	for(i=0;i<Obs.n;i++) {
		//if(El[i]*R2D>0 && El[i]*R2D<10) continue;  //�����˵�Obs�Ѿ����Ź���ģ����Բ��У���ע��
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(CycleSlipMark[j][i]==1) {
                SlipAcountL[Obs.data[i].sat-1][j]+=1;
            }
        }
	}
	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		if(!markExist[i]) continue;

		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);

		int tempSlipL = SlipAcountL[i][0];
		for(j=0;j<NFREQ+NEXOBS;j++) {
			SlipTALsum[iSys][1+j] += SlipAcountL[i][j];
			if(SlipAcountL[i][j]>tempSlipL)
				tempSlipL = SlipAcountL[i][j];
		}
		SlipAcount[i] = tempSlipL;
	}
	for(i=0;i<MAXSAT;i++) {
    	if(!(satsys(i+1,NULL)&NavSys)) continue;
		if (SatMask[i]) continue;
		if(!markExist[i]) continue;

		char id[5],*p; satno2id(i+1,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		SlipTALsum[iSys][0] += SlipAcount[i];
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		if(SlipTALsum[i][0]==0)
            summaryVal_sys[i][1] = (double)TALsum[i][0];
		else
			summaryVal_sys[i][1] =(double)TALsum[i][0]/(double)SlipTALsum[i][0];
	}
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(SlipTALsum[i][1+j]==0) {
                    summaryVal[i][j][1] = (double)TALsum[i][1+j];
				}
				else {
					summaryVal[i][j][1] = (double)TALsum[i][1+j]/(double)SlipTALsum[i][1+j];
				}
			}
		}

	}

}

void __fastcall TrtkplotMainWindow::s_ComputeMP()
{
	sortobs(&Obs);
	int i,j,k,fre;
	char syscodes[]="GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	double aMPvals[6][NFREQ+NEXOBS] = {0.0}; int numMPvals[6][NFREQ+NEXOBS] = {0};
	for (i=0;i<Obs.n;i++) {
		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
        int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
            int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
				FcodeVal[iSys][j] = codeval;
				if(fabs(Mp[j][i])>=0.0000000001) {
                	numMPvals[iSys][j] += 1;
					aMPvals[iSys][j] += fabs(Mp[j][i]);
                }
			}
		}
	}

	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
    for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		double gll_sum = 0.0; int gll_n=0;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
                gll_n += 1;
				if(numMPvals[i][j]==0)
                    summaryVal[i][j][2]=0.0;
				else
					summaryVal[i][j][2]= aMPvals[i][j]/numMPvals[i][j];
                gll_sum += summaryVal[i][j][2];
			}
		}
		if(gll_n==0)  summaryVal_sys[i][2] =0.0;
		else summaryVal_sys[i][2] = gll_sum/gll_n;
    }
	
}

void __fastcall TrtkplotMainWindow::s_ComputeCNR()
{
	sortobs(&Obs);
	int i,j,k,fre;
	char syscodes[] = "GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	double aCNRvals[6][NFREQ+NEXOBS] = {0.0}; int numCNRvals[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			int codeval = (int)Obs.data[i].code[j];
			if(codeval!=0) {
				FcodeVal[iSys][j] = codeval;
				if(Obs.data[i].SNR[j] >0.0) {
					numCNRvals[iSys][j] += 1;
					aCNRvals[iSys][j] += Obs.data[i].SNR[j]*0.25;
                }
            }
        }
	}

	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++){
		if(!(sysval[i]&NavSys)) continue;
        double gll_sum = 0.0; int gll_n = 0;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(numCNRvals[i][j]==0)
                    summaryVal[i][j][3]= 0.0;
				else
					summaryVal[i][j][3] = aCNRvals[i][j]/numCNRvals[i][j];
                gll_n +=1; gll_sum+=summaryVal[i][j][3];
			}
		}
		if(gll_n==0) summaryVal_sys[i][3] = 0.0;
        else summaryVal_sys[i][3] = gll_sum/gll_n;
	}
	
}

void __fastcall TrtkplotMainWindow::s_ComputePn(int FcodeVal[][NFREQ+NEXOBS])
{
	quick_sort(Intervals, 0, NObs-1);
	double interval = stacount(Intervals, NObs);

	sortobs1(&Obs);
	int i,j,k,l,m,fre;  char syscodes[] = "GREJSC";
	double Pns[MAXSAT][NFREQ+NEXOBS] = {0}; int markExist[MAXSAT] = {0};
	double aPnvals[6][NFREQ+NEXOBS] = {0.0}; int numPnvals[6][NFREQ+NEXOBS]={0};
    for(i=0;i<Obs.n;i=j){
		for(j=i;j<Obs.n;j++){
            if(Obs.data[j].sat!=Obs.data[i].sat) break;
		}
        if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		int *indexs = (int*)malloc(sizeof(int)*(j-i));
		int i_count=0;
		indexs[i_count++]=i;
		for(k=1;k<j-i;k++){
			if(timediff(Obs.data[i+k].time,Obs.data[i+k-1].time)>10*interval){
				indexs[i_count++]=i+k-1;
				indexs[i_count++]=i+k;
			}
		}
		indexs[i_count++]=j-1;

		char id[5],*p; satno2id(Obs.data[i].sat, id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(l=0;l<NFREQ+NEXOBS;l++){
			double tempsum =0;
			for(k=0;k<i_count;k=k+2){
				double *Ps=(double*)malloc(sizeof(double)*(indexs[k+1]-indexs[k]+1));
				int Ps_count=0;
				for(m=indexs[k];m<=indexs[k+1];m++){
					if((int)(Obs.data[m].P[l])!=0)
						Ps[Ps_count++]=Obs.data[m].P[l];
				}
				//revals = ployFitPn(Ps,Ps_count,10,re_count); //order=10
				//revals = ployFilPnAll(Ps,Ps_count);
				if(Ps_count>=10)
					tempsum += ployFitPn(Ps,Ps_count,10);

				free(Ps); Ps=NULL;
			}

			Pns[Obs.data[i].sat-1][l] = tempsum/(i_count/2);
			markExist[Obs.data[i].sat-1] = 1;

			if(Pns[Obs.data[i].sat-1][l]>0.0) {
				aPnvals[iSys][l] += Pns[Obs.data[i].sat-1][l];
				numPnvals[iSys][l] += 1;
			}
		}

	}

	/*int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			int codeval = (int)Obs.data[i].code[j];
			if(codeval!=0) {
				FcodeVal[iSys][j] = codeval;
            }
        }
	}*/

	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
    	if(!(sysval[i]&NavSys)) continue;
		double gll_sum=0.0; int gll_n =0;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(numPnvals[i][j]==0)
                    summaryVal[i][j][4] = 0.0;
				else
					summaryVal[i][j][4] = aPnvals[i][j]/numPnvals[i][j];
				gll_n += 1; gll_sum += summaryVal[i][j][4];
			}
		}
		if(gll_n==0) summaryVal_sys[i][4] = 0.0;
		else summaryVal_sys[i][4] = gll_sum/gll_n;
    }

}

void __fastcall TrtkplotMainWindow::s_ComputeCn(int FcodeVal[][NFREQ+NEXOBS])
{
	sortobs1(&Obs);
	int i,j,k,l,fre; char syscodes[] = "GREJSC";
	double Cns[MAXSAT][NFREQ+NEXOBS] = {0}; int markExist[MAXSAT]={0};
	double aCnvals[6][NFREQ+NEXOBS] = {0.0}; int numCnvals[6][NFREQ+NEXOBS] = {0};
	for(i=0;i<Obs.n;i=j){
		for(j=i;j<Obs.n;j++){
            if(Obs.data[j].sat!=Obs.data[i].sat) break;
		}
        if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;

		char id[5],*p; satno2id(Obs.data[i].sat, id);
		p = strchr(syscodes,id[0]);
		int iSys = (int)(p-syscodes);
		//fprintf(fp,"%-5s",id);
		for(l=0;l<NFREQ+NEXOBS;l++){
            double *Ls = (double*)malloc(sizeof(double)*(j-i));
			for(k=0;k<j-i;k++){
				//if(Obs.data[i+k].L[l]>0.0)
				Ls[k]=Obs.data[i+k].L[l];
			}
			Cns[Obs.data[i].sat-1][l] = compueMdiff(Ls,j-i,3);
			markExist[Obs.data[i].sat-1] = 1;

			if(Cns[Obs.data[i].sat-1][l]>0.0) {
				aCnvals[iSys][l] += Cns[Obs.data[i].sat-1][l];
				numCnvals[iSys][l] += 1;
			}
			//fprintf(fp,"%-10.5f",Cns[Obs.data[i].sat-1][l]);
		}
		//fprintf(fp,"\n");
	}

	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
    	if(!(sysval[i]&NavSys)) continue;
		double gll_sum = 0.0; int gll_n = 0;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				if(numCnvals[i][j]==0)
					summaryVal[i][j][5]=0.0;
				else
					summaryVal[i][j][5]=aCnvals[i][j]/numCnvals[i][j];
				gll_n += 1; gll_sum += summaryVal[i][j][5];
            }
		}
		if(gll_n ==0) summaryVal_sys[i][5]=0.0;
		else summaryVal_sys[i][5]= gll_sum/gll_n;
    }
	
}

void __fastcall TrtkplotMainWindow::s_ComputeIon()
{
    sortobs(&Obs);

	int i,j,k,fre,sat;
	char syscodes[] = "GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS]={0};
	double *Iod[NFREQ+NEXOBS];
    for(i=0;i<NFREQ+NEXOBS;i++) {
		Iod[i] = new double[Obs.n];
	}

	for(i=0;i<Obs.n;i++) {
    	if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
		int iSys=(int)(p-syscodes);
		for(j=0;j<NFREQ+NEXOBS;j++) {
			Iod[j][i]=0.0;
			int codeval=(int)Obs.data[i].code[j];
			if(codeval!=0)
				FcodeVal[iSys][j] = codeval;
        }
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//compute derivative of ionospheric delay
    int numIod[6][NFREQ+NEXOBS] ={0};

	for(sat=7;sat<=MAXSAT;sat++) {
        if(!(satsys(sat,NULL)&NavSys)) continue;
		if (SatMask[sat-1]) continue;
		char id[5],*p; satno2id(sat,id);
		p = strchr(syscodes,id[0]);
		int iSys=(int)(p-syscodes);

		for(i=0;i<NFREQ+NEXOBS;i++) {
            if(FcodeVal[iSys][i]==0) continue;
            double ion0=0,ion1=0;gtime_t t0={0},t1={0};
			for(j=0;j<Obs.n;j++) {
				if(Obs.data[j].sat!=sat) continue;

				ion0=ion1; t0=t1;
				ion1 = Ion[i][j]; t1=Obs.data[j].time;

				//if(Obs.data[0].time.time==t0.time&&Obs.data[0].time.sec==t0.sec) continue;
                if(t0.time==0 && t0.sec<0.00000001) continue;

				Iod[i][j]=100*(ion1-ion0)/(timediff(t1,t0)/60);

				if(Iod[i][j]>400) {
                    numIod[iSys][i] += 1;
                }
			}

        }
    }

	/////////////////////////////////////////////////////////////////////////////////////////////////////

	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		double gll_sum=0; int gll_n = 0;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				summaryVal[i][j][6] = numIod[i][j];
				gll_n += 1; gll_sum += summaryVal[i][j][6];
			}
		}
        summaryVal_sys[i][6] = gll_sum/gll_n;
    }
    
}

void __fastcall TrtkplotMainWindow::ComputeSummary(AnsiString file)
{
	AnsiString asFileName = file;
	Variant varApp,varDoc,varActiveDoc;
	Variant word_select;
    Variant word_table;
    Variant word_paras;
    Variant word_para;
    Variant start_cell;
    Variant end_cell;
	Variant my_cell;
	int i,j;
	int nRowCount;
	int nColCount;

	//char wordcodetype[NFREQ+NEXOBS][3]; int wordcodemark,fre;
	AnsiString wordcodetype[NFREQ+NEXOBS]; 
	int wordcodeIndex[NFREQ+NEXOBS],wordcodemark,fre;
	int sysindex;
    char syscodes[]="GREJSC";
	int FcodeVal[6][NFREQ+NEXOBS] = {0};
	for (i=0;i<Obs.n;i++) {
		if(!(satsys(Obs.data[i].sat,NULL)&NavSys)) continue;
		if (SatMask[Obs.data[i].sat-1]) continue;
		char id[5],*p; satno2id(Obs.data[i].sat,id);
		p = strchr(syscodes,id[0]);
        int iSys = (int)(p-syscodes);
		for (j=0;j<NFREQ+NEXOBS;j++) {
			int codeval = (int)Obs.data[i].code[j];
			if(codeval !=0) {
				FcodeVal[iSys][j] = codeval;
            }
		}
	}

	ReadWaitStart();

	s_ComputeDataIntergirtyRate(FcodeVal); //��������������
	s_ComputeObservationPerSlip(FcodeVal); //������
	s_ComputeMP(); //�ྶ
	s_ComputeCNR(); //�����
	s_ComputePn(FcodeVal); //α������
	s_ComputeCn(FcodeVal); //��λ����
	s_ComputeIon();  //���������
	//�ۺ�����
	double ADataIntegrityRate=1.0,AObservationPerSlip=1000000,AMP=0.001,ACNR=70.0,APn = 0.00001,ACn = 0.000001,AIon = 0.001;
	int sysval[6] = {SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP};
	for(i=0;i<6;i++) {
		if(!(sysval[i]&NavSys)) continue;
		for(j=0;j<NFREQ+NEXOBS;j++) {
			if(FcodeVal[i][j]!=0) {
				double reVal = sqrtdxy(ADataIntegrityRate,summaryVal[i][j][0]) + sqrtdxy(AObservationPerSlip,summaryVal[i][j][1]) +
				sqrtdxy(AMP,summaryVal[i][j][2]) + sqrtdxy(ACNR,summaryVal[i][j][3]) + sqrtdxy(APn,summaryVal[i][j][4]) +
				sqrtdxy(ACn,summaryVal[i][j][5]) +  sqrtdxy(AIon,summaryVal[i][j][6]);
				summaryVal[i][j][7]=reVal;
            }
		}
		summaryVal_sys[i][7] = sqrtdxy(ADataIntegrityRate,summaryVal_sys[i][0]) + sqrtdxy(AObservationPerSlip,summaryVal_sys[i][1]) +
				sqrtdxy(AMP,summaryVal_sys[i][2]) + sqrtdxy(ACNR,summaryVal_sys[i][3]) + sqrtdxy(APn,summaryVal_sys[i][4]) +
				sqrtdxy(ACn,summaryVal_sys[i][5]) +  sqrtdxy(AIon,summaryVal_sys[i][6]);
    }


	if(ExtractFileExt(A2U(file)) != ".doc" && ExtractFileExt(A2U(file)) != ".docx") {
    	FILE *fp;
		//AnsiString file = "F:\\Users\\dell\\Desktop\\test.txt";
		if(!(fp=fopen(file.c_str(),"w"))) return;

        int chn=80;

		fprintf(fp,"%s\n","GNSS�������������������");
		for(i=0;i<chn;i++) fprintf(fp,"%s","-");  fprintf(fp,"\n");
        #pragma region outgps
		fprintf(fp,"%s\n","һ��GPSϵͳ");
        sysindex =0;  //GPS
		nRowCount = 10;
		nColCount = 1;
		wordcodemark=0;
		for(i=0;i<NFREQ+NEXOBS;i++) {
			wordcodeIndex[i]=0;
			wordcodetype[i]="";
		}
		for(i=0;i<NFREQ+NEXOBS;i++) {
			if(FcodeVal[sysindex][i]!=0) {
				wordcodeIndex[wordcodemark] = i;
				wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
				wordcodemark+=1;
				nColCount += 1;
			}
		}
		//
		fprintf(fp,"%-20s%s","Ƶ������",":");
		fprintf(fp,"%12s","sys");
		for(i=0;i<nColCount-1;i++)
            fprintf(fp,"%12s",wordcodetype[i].c_str());
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����������",":");
        fprintf(fp,"%12.2f",summaryVal_sys[sysindex][0]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][0]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][1]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][1]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ྶ��m��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][2]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][2]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����ȣ�dBHz��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][3]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][3]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","α��������m��",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][4]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][4]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ز���λ�������ܣ�",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][5]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][5]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������ӳ�����",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][6]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][6]);
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ۺ���������",":");
		fprintf(fp,"%36.2f",summaryVal_sys[sysindex][7]);
		//for(i=0;i<nColCount-1;i++)
		//	fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][7]);
        fprintf(fp,"\n");
        #pragma end_region

        #pragma region BDS
		for(i=0;i<chn;i++)  fprintf(fp,"%s","*");  fprintf(fp,"\n");
		fprintf(fp,"%s\n","����BDSϵͳ");
        sysindex = 5;
		nRowCount = 10;
		nColCount = 1;
		wordcodemark=0;
		for(i=0;i<NFREQ+NEXOBS;i++) {
			wordcodeIndex[i]=0;
			wordcodetype[i]="";
		}
		for(i=0;i<NFREQ+NEXOBS;i++) {
			if(FcodeVal[sysindex][i]!=0) {
				wordcodeIndex[wordcodemark] = i;
				wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
				wordcodemark+=1;
				nColCount += 1;
			}
		}
        //
		fprintf(fp,"%-20s%s","Ƶ������",":");
        fprintf(fp,"%12s","sys");
		for(i=0;i<nColCount-1;i++)
            fprintf(fp,"%12s",wordcodetype[i].c_str());
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����������",":");
		fprintf(fp,"%12.2f",summaryVal_sys[sysindex][0]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][0]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][1]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][1]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ྶ��m��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][2]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][2]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����ȣ�dBHz��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][3]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][3]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","α��������m��",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][4]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][4]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ز���λ�������ܣ�",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][5]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][5]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������ӳ�����",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][6]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][6]);
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ۺ���������",":");
		fprintf(fp,"%36.2f",summaryVal_sys[sysindex][7]);
		//for(i=0;i<nColCount-1;i++)
		//	fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][7]);
		fprintf(fp,"\n");
		#pragma end_region

        #pragma region GLONASS
		for(i=0;i<chn;i++) fprintf(fp,"%s","*");  fprintf(fp,"\n");
		fprintf(fp,"%s\n","����GLONASSϵͳ");
        sysindex = 1; //GLONSASS
		nRowCount = 10;
		nColCount = 1;
		wordcodemark=0;
		for(i=0;i<NFREQ+NEXOBS;i++) {
			wordcodeIndex[i]=0;
			wordcodetype[i]="";
		}
		for(i=0;i<NFREQ+NEXOBS;i++) {
			if(FcodeVal[sysindex][i]!=0) {
				wordcodeIndex[wordcodemark] = i;
				wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
				wordcodemark+=1;
				nColCount += 1;
			}
		}
        //
		fprintf(fp,"%-20s%s","Ƶ������",":");
		fprintf(fp,"%12s","sys");
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12s",wordcodetype[i].c_str());
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����������",":");
		fprintf(fp,"%12.2f",summaryVal_sys[sysindex][0]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][0]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][1]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][1]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ྶ��m��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][2]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][2]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����ȣ�dBHz��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][3]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][3]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","α��������m��",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][4]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][4]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ز���λ�������ܣ�",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][5]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][5]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������ӳ�����",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][6]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][6]);
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ۺ���������",":");
		fprintf(fp,"%36.2f",summaryVal_sys[sysindex][7]);
		//for(i=0;i<nColCount-1;i++)
		//	fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][7]);
		fprintf(fp,"\n");
		#pragma end_region

        #pragma region GALILEO
		for(i=0;i<chn;i++) fprintf(fp,"%s","*");  fprintf(fp,"\n");
		fprintf(fp,"%s\n","�ġ�GALILEOϵͳ");
		sysindex = 2; //GALILEO
		nRowCount = 10;
		nColCount = 1;
		wordcodemark=0;
		for(i=0;i<NFREQ+NEXOBS;i++) {
			wordcodeIndex[i]=0;
			wordcodetype[i]="";
		}
		for(i=0;i<NFREQ+NEXOBS;i++) {
			if(FcodeVal[sysindex][i]!=0) {
				wordcodeIndex[wordcodemark] = i;
				wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
				wordcodemark+=1;
				nColCount += 1;
			}
		}
        //
		fprintf(fp,"%-20s%s","Ƶ������",":");
		fprintf(fp,"%12s","sys");
		for(i=0;i<nColCount-1;i++)
            fprintf(fp,"%12s",wordcodetype[i].c_str());
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����������",":");
		fprintf(fp,"%12.2f",summaryVal_sys[sysindex][0]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][0]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][1]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][1]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ྶ��m��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][2]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][2]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","����ȣ�dBHz��",":");
		fprintf(fp,"%12.4f",summaryVal_sys[sysindex][3]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.4f",summaryVal[sysindex][wordcodeIndex[i]][3]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","α��������m��",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][4]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][4]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ز���λ�������ܣ�",":");
		fprintf(fp,"%12.5f",summaryVal_sys[sysindex][5]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.5f",summaryVal[sysindex][wordcodeIndex[i]][5]);
		fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","������ӳ�����",":");
		fprintf(fp,"%12.0f",summaryVal_sys[sysindex][6]);
		for(i=0;i<nColCount-1;i++)
			fprintf(fp,"%12.0f",summaryVal[sysindex][wordcodeIndex[i]][6]);
        fprintf(fp,"\n");
		//
		fprintf(fp,"%-20s%s","�ۺ���������",":");
		fprintf(fp,"%36.2f",summaryVal_sys[sysindex][7]);
		//for(i=0;i<nColCount-1;i++)
		//	fprintf(fp,"%12.2f",summaryVal[sysindex][wordcodeIndex[i]][7]);
		fprintf(fp,"\n");
		#pragma end_region

        for(i=0;i<chn;i++) fprintf(fp,"%s","-");   fprintf(fp,"\n");

        fclose(fp);
	}
	else {
		try {
			varApp = CreateOleObject("Word.Application");
		} catch (...) {
			Application->MessageBox(L"���������ȷ�����Ѿ���ȷ��װ��MS Office!",L"����",MB_OK);
			return;
		}

		try {
			try {
				varApp.Exec(PropertySet("Visible")<<false);
				varDoc=varApp.OlePropertyGet("Documents");
				varDoc.OleProcedure("Add");
				varActiveDoc=varApp.OlePropertyGet("ActiveDocument");
				varActiveDoc.Exec(Procedure("SaveAs")<<asFileName);
				////////////////////////////////////////////////////////////////////////////
				word_select = varApp.OlePropertyGet("Selection");
				//���ӵ�һ��
				word_select.OlePropertyGet("Font").OlePropertySet("Size", 20);
				word_select.OlePropertyGet("Font").OlePropertySet("Name", WideString("����"));
				word_select.OlePropertyGet("ParagraphFormat").OlePropertySet("Alignment", 1);
				word_select.OleProcedure("TypeText", WideString("LSNPADPS�������������������"));
				//��������
				word_select.OlePropertyGet("Font").OlePropertySet("Size", 10);
				word_select.OlePropertyGet("Font").OlePropertySet("Name", WideString("����"));
				//�������1
				sysindex =0;  //GPS
				nRowCount = 10;
				nColCount = 2;
				wordcodemark=0;
				for(i=0;i<NFREQ+NEXOBS;i++) {
					wordcodeIndex[i]=0;
					wordcodetype[i]="";
				}
				for(i=0;i<NFREQ+NEXOBS;i++) {
					if(FcodeVal[sysindex][i]!=0) {
						wordcodeIndex[wordcodemark] = i;
						wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
						wordcodemark+=1;
						nColCount += 1;
					}
				}
				varActiveDoc.OlePropertyGet("Tables").OleProcedure("Add", word_select.OlePropertyGet("Range"), nRowCount, nColCount, 1, 0);
				word_table = varActiveDoc.OlePropertyGet("Tables").OleFunction("Item", 1);
				//�ϲ���Ԫ�� ����ͷ  //(1, 1)-(1, nColCount)�ϲ�Ϊ(1, 1)
				start_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)1);
				if(nColCount>1) {
					end_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)nColCount);
					start_cell.OleProcedure("Merge", end_cell);
				}
				start_cell.OlePropertySet("Range", WideString("һ��GPSϵͳ"));
				//
				my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("Ƶ������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)i+2);
					if(i==0) my_cell.OlePropertySet("Range",WideString("sys"));
					else my_cell.OlePropertySet("Range", WideString(wordcodetype[i-1]));
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)i+2);
					if(i==0) {
						char temp_val[13]; sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][0]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
					}
					else {
						char temp_val[13]; sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][0]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)i+2);
					if(i==0) {
						char temp_val[13]; sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][1]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13]; sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][1]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ྶ��m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)i+2);
					if(i==0) {
						char temp_val[13]; sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][2]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
					}
					else {
						char temp_val[13]; sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][2]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����ȣ�dBHz��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)i+2);
					if(i==0) {
						char temp_val[13]; sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][3]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13]; sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][3]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("α��������m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][4]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
                        char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i-1]][4]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ز���λ�������ܣ�"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][5]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i-1]][5]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������ӳ�����"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][6]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][6]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ۺ���������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][7]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][7]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}

                //���ӵڶ���
				word_select.OleProcedure("EndKey", 6);
				word_select.OleProcedure("TypeText", WideString("\n"));
				//�������4
				sysindex = 5;    //BDS
				nRowCount = 10;
				nColCount = 2;
				wordcodemark=0;
				for(i=0;i<NFREQ+NEXOBS;i++) {
					wordcodeIndex[i]=0;
					wordcodetype[i]="";
				}
				for(i=0;i<NFREQ+NEXOBS;i++) {
					if(FcodeVal[sysindex][i]!=0) {
						wordcodeIndex[wordcodemark] = i;
						wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
						wordcodemark+=1;
						nColCount += 1;
					}
				}
				varActiveDoc.OlePropertyGet("Tables").OleProcedure("Add", word_select.OlePropertyGet("Range"), nRowCount, nColCount, 1, 0);
				word_table = varActiveDoc.OlePropertyGet("Tables").OleFunction("Item", 2);
				//�ϲ���Ԫ�� ����ͷ  //(1, 1)-(1, nColCount)�ϲ�Ϊ(1, 1)
				start_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)1);
				if(nColCount>1) {
					end_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)nColCount);
					start_cell.OleProcedure("Merge", end_cell);
				}
				start_cell.OlePropertySet("Range", WideString("����BDSϵͳ"));
				//
				my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("Ƶ������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)i+2);
					if(i==0) my_cell.OlePropertySet("Range", WideString("sys"));
					else my_cell.OlePropertySet("Range", WideString(wordcodetype[i-1]));
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][0]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
                        char temp_val[13];sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][0]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][1]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][1]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ྶ��m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][2]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][2]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����ȣ�dBHz��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][3]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][3]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("α��������m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][4]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i]][4]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ز���λ�������ܣ�"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][5]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i-1]][5]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������ӳ�����"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][6]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][6]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ۺ���������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][7]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][7]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}

				//���ӵ�����
				word_select.OleProcedure("EndKey", 6);
				word_select.OleProcedure("TypeText", WideString("\n"));
				//�������2
				sysindex = 1; //GLONSASS
				nRowCount = 10;
				nColCount = 2;
				wordcodemark=0;
				for(i=0;i<NFREQ+NEXOBS;i++) {
					wordcodeIndex[i]=0;
					wordcodetype[i]="";
				}
				for(i=0;i<NFREQ+NEXOBS;i++) {
					if(FcodeVal[sysindex][i]!=0) {
						wordcodeIndex[wordcodemark] = i;
						wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
						wordcodemark+=1;
						nColCount += 1;
					}
				}
				varActiveDoc.OlePropertyGet("Tables").OleProcedure("Add", word_select.OlePropertyGet("Range"), nRowCount, nColCount, 1, 0);
				word_table = varActiveDoc.OlePropertyGet("Tables").OleFunction("Item", 3);
				//�ϲ���Ԫ�� ����ͷ  //(1, 1)-(1, nColCount)�ϲ�Ϊ(1, 1)
				start_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)1);
				if(nColCount>1) {
					end_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)nColCount);
					start_cell.OleProcedure("Merge", end_cell);
				}
				start_cell.OlePropertySet("Range", WideString("����GLONASSϵͳ"));
				//
				my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("Ƶ������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)i+2);
                    if(i==0) my_cell.OlePropertySet("Range", WideString("sys"));
					else my_cell.OlePropertySet("Range", WideString(wordcodetype[i-1]));
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][0]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][0]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][1]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][1]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ྶ��m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][2]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][2]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����ȣ�dBHz��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][3]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][3]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("α��������m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][4]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i-1]][4]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ز���λ�������ܣ�"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)i+2);
					if(i==0){
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][5]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i-1]][5]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������ӳ�����"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][6]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][6]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ۺ���������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][7]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][7]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}

				//���ӵ��Ķ�
				word_select.OleProcedure("EndKey", 6);
				word_select.OleProcedure("TypeText", WideString("\n"));
				//�������3
				sysindex = 2; //GALILEO
				nRowCount = 10;
				nColCount = 2;
				wordcodemark=0;
				for(i=0;i<NFREQ+NEXOBS;i++) {
					wordcodeIndex[i]=0;
					wordcodetype[i]="";
				}
				for(i=0;i<NFREQ+NEXOBS;i++) {
					if(FcodeVal[sysindex][i]!=0) {
						wordcodeIndex[wordcodemark] = i;
						wordcodetype[wordcodemark] = (AnsiString)code2obs(FcodeVal[sysindex][i],&fre);
						wordcodemark+=1;
						nColCount += 1;
					}
				}
				varActiveDoc.OlePropertyGet("Tables").OleProcedure("Add", word_select.OlePropertyGet("Range"), nRowCount, nColCount, 1, 0);
				word_table = varActiveDoc.OlePropertyGet("Tables").OleFunction("Item", 4);
				//�ϲ���Ԫ�� ����ͷ  //(1, 1)-(1, nColCount)�ϲ�Ϊ(1, 1)
				start_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)1);
				if(nColCount>1) {
					end_cell = word_table.OleFunction("Cell", (Variant)1, (Variant)nColCount);
					start_cell.OleProcedure("Merge", end_cell);
				}
				start_cell.OlePropertySet("Range", WideString("�ġ�GALILEOϵͳ"));
				//
				my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("Ƶ������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)2, (Variant)i+2);
					if(i==0) {
						my_cell.OlePropertySet("Range", WideString("sys"));
                    }
					else {
						my_cell.OlePropertySet("Range", WideString(wordcodetype[i-1]));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)3, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][0]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][0]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)4, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][1]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][1]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ྶ��m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)5, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][2]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][2]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("����ȣ�dBHz��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)6, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal_sys[sysindex][3]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.4f",summaryVal[sysindex][wordcodeIndex[i-1]][3]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("α��������m��"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)7, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][4]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i-1]][4]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ز���λ�������ܣ�"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)8, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal_sys[sysindex][5]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.5f",summaryVal[sysindex][wordcodeIndex[i-1]][5]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("������ӳ�����"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)9, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal_sys[sysindex][6]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
                    }
					else {
						char temp_val[13];sprintf(temp_val,"%.0f",summaryVal[sysindex][wordcodeIndex[i-1]][6]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}
				//
				my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)1);
				my_cell.OlePropertySet("Range", WideString("�ۺ���������"));
				for(i=0;i<nColCount-1;i++) {
					my_cell = word_table.OleFunction("Cell", (Variant)10, (Variant)i+2);
					if(i==0) {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal_sys[sysindex][7]);
						my_cell.OlePropertySet("Range",WideString(temp_val));
					}
					else {
						char temp_val[13];sprintf(temp_val,"%.2f",summaryVal[sysindex][wordcodeIndex[i-1]][7]);
						my_cell.OlePropertySet("Range", WideString(temp_val));
                    }
				}

				//////////////////////////////////////////////////////////////////////////////////////////

				varActiveDoc.OleProcedure("Save");
			} catch (EOleSysError &E) {
				Application->MessageBox(E.Message.c_str(),L"����",MB_OK);
				return;
			} catch (EOleError &E) {
				Application->MessageBox(E.Message.c_str(),L"����",MB_OK);
				return;
			}
		}
		__finally {
			varApp.OleFunction("Quit");
		}
	}

    ReadWaitEnd();

	
}

