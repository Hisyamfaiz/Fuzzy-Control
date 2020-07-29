/*Readme
1. Membership Function Eror & Delta Eror must be change based on your plan or your design
2. this code use 7x7 Rulebase
3. to avoid overshoot and oscillation during tracking to reach set point, you should change singleton value
4. singleton effect on addition step of fuzzy output
*/
//--------------FUZZY variable initialization----------------//

//Membership Function Eror
float MF_e1=(-6), MF_e2=(-4), MF_e3=(-2), MF_ez=0, MF_e4=2, MF_e5=4, MF_e6=6;

//Membership Function Delta Eror
float MF_d1=(-6), MF_d2=(-4), MF_d3=(-2), MF_dz=0, MF_d4=2, MF_d5=4, MF_d6=6;

//derajat keanggotaan
float eNB, eNM, eNS, eZ, ePS, ePM, ePB;
float dNB, dNM, dNS, dZ, dPS, dPM, dPB;

//Rule base variable
float r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15;
float r16, r17, r18, r19, r20, r21, r22, r23, r24;
float r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35;
float r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49;

//Other variable
float A,B,e,d,sp,pv,esblm,C,D,E,F,G,H,I,J,dc,step,duty;

//Singleton
float outNH=-0.05, outNB=-0.025, outNM=-0.01, outNS=-0.005, outZ=0, outPS=0.005, outPM=0.01, outPB=0.025, outPH=0.05;

//------------end of FUZZY variable initialization-----------//


void FUZZY()
{
	pv = SENSOR_FEEDBACK;
	sp = SETPOINT;
	e = sp-pv;
	d = e-esblm;
	esblm = e;

	///////////////////////////FUZZIFICATION error//////////////////////////////

	if(e<=MF_e1)
	{ eNB=1;  eNM=eNS=eZ=ePS=ePM=ePB=0;}

	if(e>=MF_e1&&e<=MF_e2)
	{ eNB=(MF_e2-e)/(MF_e2-MF_e1);
	   eNM=(e-MF_e1)/(MF_e2-MF_e1);
	   eNS=eZ=ePS=ePM=ePB=0;
	}

	else if(e>=MF_e2&&e<=MF_e3)
	{ eNM=(MF_e3-e)/(MF_e3-MF_e2);
	   eNS=(e-MF_e2)/(MF_e3-MF_e2);
	   eNB=eZ=ePS=ePM=ePB=0;
	}

	else if(e>=MF_e3&&e<=MF_ez)
	{ eNS=(MF_ez-e)/(MF_ez-MF_e3);
	   eZ=(e-MF_e3)/(MF_ez-MF_e3);
	   eNB=eNM=ePS=ePM=ePB=0;
	}

	else if(e>=MF_ez&&e<=MF_e4)
	{ eZ=(MF_e4-e)/(MF_e4-MF_ez);
	   ePS=(e-MF_ez)/(MF_e4-MF_ez);
	   eNB=eNM=eNS=ePM=ePB=0;
	}

	else if(e>=MF_e4&&e<=MF_e5)
	{ ePS=(MF_e5-e)/(MF_e5-MF_e4);
	   ePM=(e-MF_e4)/(MF_e5-MF_e4);
	   eNB=eNM=eNS=eZ=ePB=0;
	}

	else if(e>=MF_e5&&e<=MF_e6)
	{ ePM=(MF_e6-e)/(MF_e6-MF_e5);
	   ePM=(e-MF_e5)/(MF_e6-MF_e5);
	   eNB=eNM=eNS=eZ=ePS=0;
	}

	else if(e>=MF_e6)
	{ ePB=1; eNB=eNM=eNS=eZ=ePS=ePM=0;}

	/////////////////////FUZZIFICATION delta error //////////////
	if(d<=MF_d1)
	{ dNB=1;  dNM=dNS=dZ=dPS=dPM=dPB=0;}

	if(d>=MF_d1&&d<=MF_d2)
	{ dNB=(MF_d2-d)/(MF_d2-MF_d1);
	   dNM=(d-MF_d1)/(MF_d2-MF_d1);
	   dNS=dZ=dPS=dPM=dPB=0;
	}

	else if(d>=MF_d2&&d<=MF_d3)
	{ dNM=(MF_d3-d)/(MF_d3-MF_d2);
	   dNS=(d-MF_d2)/(MF_d3-MF_d2);
	   dNB=dZ=dPS=dPM=dPB=0;
	}

	else if(d>=MF_d3&&d<=MF_dz)
	{ dNS=(MF_dz-d)/(MF_dz-MF_d3);
	   dZ=(d-MF_d3)/(MF_dz-MF_d3);
	   dNB=dNM=dPS=dPM=dPB=0;
	}

	else if(d>=MF_dz&&d<=MF_d4)
	{ dZ=(MF_d4-d)/(MF_d4-MF_dz);
	   dPS=(d-MF_dz)/(MF_d4-MF_dz);
	   dNB=dNM=dNS=dPM=dPB=0;
	}

	else if(d>=MF_d4&&d<=MF_d5)
	{ dPS=(MF_d5-d)/(MF_d5-MF_d4);
	   dPM=(d-MF_d4)/(MF_d5-MF_d4);
	   dNB=dNM=dNS=dZ=dPB=0;
	}

	else if(d>=MF_d5&&d<=MF_d6)
	{ dPM=(MF_d6-d)/(MF_d6-MF_d5);
	   dPB=(d-MF_d5)/(MF_d6-MF_d5);
	   dNB=dNM=dNS=dZ=dPS=0;
	}

	else if(d>=MF_d6)
	{ dPB=1; dNB=dNM=dNS=dZ=dPS=dPM=0;}

	/////////////////////INFERENSI / rule base///////////////////////

	r1=dPB; if(eNB<dPB) r1=eNB;		//r1=max(dPB,eNB);
	r2=dPB; if(eNM<dPB) r2=eNM;		//r2=max(dPB,eNM);
	r3=dPB; if(eNS<dPB) r3=eNS;		//r3=max(dPB,eNS);
	r4=dPB; if(eZ<dPB) r4=eZ;		//r4=max(dPB,eZ);
	r5=dPB; if(ePS<dPB) r5=ePS;		//r5=max(dPB,ePS);
	r6=dPB; if(ePM<dPB) r6=ePM;		//r6=max(dPB,ePM);
	r7=dPB; if(ePB<dPB) r7=ePB;		//r7=max(dPB,ePB);


	r8=dPM; if(eNB<dPM) r8=eNB;		//r8=max(dPM,eNB);
	r9=dPM; if(eNM<dPM) r9=eNM;		//r9=max(dPM,eNM);
	r10=dPM; if(eNS<dPM) r10=eNS;	//r10=max(dPM,eNS);
	r11=dPM; if(eZ<dPM) r11=eZ;		//r11=max(dPM,eZ);
	r12=dPM; if(ePS<dPM) r12=ePS;	//r12=max(dPM,ePS);
	r13=dPM; if(ePM<dPM) r13=ePM;	//r13=max(dPM,ePM);
	r14=dPM; if(ePB<dPM) r14=ePB;	//r14=max(dPM,ePB);

	r15=dPS; if(eNB<dPS) r15=eNB;	//r15=max(dPS,eNB);
	r16=dPS; if(eNM<dPS) r16=eNM;	//r16=max(dPS,eNM);
	r17=dPS; if(eNS<dPS) r17=eNS;	//r17=max(dPS,eNS);
	r18=dPS; if(eZ<dPS) r18=eZ;		//r18=max(dPS,eZ);
	r19=dPS; if(ePS<dPS) r19=ePS;	//r19=max(dPS,ePS);
	r20=dPS; if(ePM<dPS) r20=ePM;	//r20=max(dPS,ePM);
	r21=dPS; if(ePB<dPS) r21=ePB;	//r21=max(dPS,ePB);

	r22=dZ; if(eNB<dZ) r22=eNB;		//r22=max(dZ,eNB);
	r23=dZ; if(eNM<dZ) r23=eNM;		//r23=max(dZ,eNM);
	r24=dZ; if(eNS<dZ) r24=eNS;		//r24=max(dZ,eNS);
	r25=dZ; if(eZ<dZ) r25=eZ;		//r25=max(dZ,eZ);
	r26=dZ; if(ePS<dZ) r26=ePS;		//r26=max(dZ,ePS);
	r27=dZ; if(ePM<dZ) r27=ePM;		//r27=max(dZ,ePM);
	r28=dZ; if(ePB<dZ) r28=ePB;		//r28=max(dZ,ePB);

	r29=dNS; if(eNB<dNS) r29=eNB;	//r29=max(dNS,eNB);
	r30=dNS; if(eNM<dNS) r30=eNM;	//r30=max(dNS,eNM);
	r31=dNS; if(eNS<dNS) r31=eNS;	//r31=max(dNS,eNS);
	r32=dNS; if(eZ<dNS) r32=eZ;		//r32=max(dNS,eZ);
	r33=dNS; if(ePS<dNS) r33=ePS;	//r33=max(dNS,ePS);
	r34=dNS; if(ePM<dNS) r34=ePM;	//r34=max(dNS,ePM);
	r35=dNS; if(ePB<dNS) r35=ePB;	//r35=max(dNS,ePB);

	r36=dNM; if(eNB<dNM) r36=eNB;	//r36=max(dNM,eNB);
	r37=dNM; if(eNM<dNM) r37=eNM;	//r37=max(dNM,eNM);
	r38=dNM; if(eNS<dNM) r38=eNS;	//r38=max(dNM,eNS);
	r39=dNM; if(eZ<dNM) r39=eZ;		//r39=max(dNM,eZ);
	r40=dNM; if(ePS<dNM) r40=ePS;	//r40=max(dNM,ePS);
	r41=dNM; if(ePM<dNM) r41=ePM;	//r41=max(dNM,ePM);
	r42=dNM; if(ePB<dNM) r42=ePB;	//r42=max(dNM,ePB);

	r43=dNB; if(eNB<dNB) r43=eNB;	//r43=max(dNB,eNB);
	r44=dNB; if(eNM<dNB) r44=eNM;	//r44=max(dNB,eNM);
	r45=dNB; if(eNS<dNB) r45=eNS;	//r45=max(dNB,eNS);
	r46=dNB; if(eZ<dNB) r46=eZ;		//r46=max(dNB,eZ);
	r47=dNB; if(ePS<dNB) r47=ePS;	//r47=max(dNB,ePS);
	r48=dNB; if(ePM<dNB) r48=ePM;	//r48=max(dNB,ePM);
	r49=dNB; if(ePB<dNB) r49=ePB;	//r49=max(dNB,ePB);

	///////////////////////////////DEFUZZIFICATION///////////////////////////////////

	A=(r1*outZ)+(r2*outPS)+(r3*outPM)+(r4*outPB)+(r5*outPH)+(r6*outPH)+(r7*outPH);
	B=(r8*outNS)+(r9*outZ)+(r10*outPS)+(r11*outPM)+(r12*outPB)+(r13*outPH)+(r14*outPH);
	C=(r15*outNM)+(r16*outNS)+(r17*outZ)+(r18*outPS)+(r19*outPM)+(r20*outPB)+(r21*outPH);
	D=(r22*outNB)+(r23*outNM)+(r24*outNS)+(r25*outZ)+(r26*outPS)+(r27*outPM)+(r28*outPB);
	E=(r29*outNH)+(r30*outNB)+(r31*outNM)+(r32*outNS)+(r33*outZ)+(r34*outPS)+(r35*outPM);
	F=(r36*outNH)+(r37*outNH)+(r38*outNB)+(r39*outNM)+(r40*outNS)+(r41*outZ)+(r42*outPS);
	G=(r43*outNH)+(r44*outNH)+(r45*outNH)+(r46*outNB)+(r47*outNM)+(r48*outNS)+(r49*outZ);

	H=r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+r13+r14+r15+r16+ r17+ r18+ r19+ r20+ r21+ r22+ r23+ r24+r25+r26+r27+r28+r29+r30+r31+r32+r33+r34+r35+r36+r37+r38+r39+r40+r41+r42+r43+r44+r45+r46+r47+r48+r49;

	step=(A+B+C+D+E+F+G)/H;

	dc=dc+step;	//output fuzzy

	if(dc>=85)
		dc=85;
	if(dc<=0)
		dc=0;

}