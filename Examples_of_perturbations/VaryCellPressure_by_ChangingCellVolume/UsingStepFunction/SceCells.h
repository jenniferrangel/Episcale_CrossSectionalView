//NOte: How hard the volume conservation should be imposed is an input in the AddLagrnagian Strcture
//      Stiffness of different locations of cells and different cells are input in ActinLevel strcture

#ifndef SCECELLS_H_
#define SCECELLS_H_

#include "SceNodes.h"
#include "SceECM.h"
#include "Solver.h"
#include <time.h>
#include <functional>
#include <thrust/tabulate.h>
#include <thrust/count.h>
#define PI 3.14159265358979

typedef thrust::tuple<double, double, SceNodeType> CVec2Type;
typedef thrust::tuple<bool, double, double> BoolDD;
typedef thrust::tuple<bool, double, int, int> BoolDII; //KevinT
typedef thrust::tuple<uint, double, double> UiDD;
typedef thrust::tuple<uint, double, double, bool> UiDDBool; //KevinT
typedef thrust::tuple<uint, double, double, bool, int, int, MembraneType1, int> UiDDBoolIITI; //KevinT
typedef thrust::tuple<double, uint, double, double, double, MembraneType1> DUiDDDT; //KevinT
typedef thrust::tuple<uint, int, int> UiII;
typedef thrust::tuple<uint, double, double, double> UiDDD; //Ali
typedef thrust::tuple<double, double, uint, bool, double,double> DDUiBDD ; 
typedef thrust::tuple<double, uint> DUi; //Ali 
typedef thrust::tuple<double, double, uint> DDUi;
typedef thrust::tuple<uint, double, double, bool> UiDDBool;//AAMIRI
typedef thrust::tuple<uint, uint> UiUi;
typedef thrust::tuple<bool, SceNodeType> boolType;
typedef thrust::tuple<double, double, bool, SceNodeType, uint> Vel2DActiveTypeRank;
typedef thrust::tuple<double, double, double, bool, double, double, double, double> DDDBDDDD;
//Ali comment 
//typedef thrust::tuple<uint, uint, uint, double, double, double, double> TensionData;
//Ali comment
//Ali
typedef thrust::tuple<double, uint, double, int ,uint, uint, double, double, double, double> TensionData;
//ChangesMadeByKT2_begin
typedef thrust::tuple<double, uint, MembraneType1, int ,uint, uint, double, double, double, double> TensionData_type2;
//ChangesMadeByKT2_end
typedef thrust::tuple<double, uint, uint, uint, double, double> DUiUiUiDD;
//ChangesMadeByKT_begin
typedef thrust::tuple<double, uint, uint, uint, double, double, MembraneType1> DUiUiUiDDT;
//ChangesMadeByKT_end
typedef thrust::tuple<double, uint, double, double,uint, uint, double, double, double, double> DUiDDUiUiDDDD;
typedef thrust::tuple<double, int, int ,uint, uint, double, double > DIIUiUiDD;
typedef thrust::tuple<ECellType,uint, double, MembraneType1 ,bool,uint, uint> ActinData; //Ali
typedef thrust::tuple<MembraneType1 ,double, double> TDD; //Ali
typedef thrust::tuple<MembraneType1,int,int> TII; //Ali
typedef thrust::tuple<bool,MembraneType1,uint ,uint> BTUiUi; //Ali
typedef thrust::tuple<ECellType,uint,double,uint ,MembraneType1, double, double> TUiDUiTDD; //Ali
//Ali 
typedef thrust::tuple<uint, uint, uint, double, double> BendData;
typedef thrust::tuple<uint, uint, uint, double, double, double, double, double, double, double> CurvatureData;//AAMIRI
typedef thrust::tuple<uint, uint, uint, uint, double, double, double> CellData;
typedef thrust::tuple<double, uint, double, double, uint, uint, bool, double, double,MembraneType1> DUiDDUiUiBDDT ;

//typedef pair<device_vector<double>::iterator,device_vector<double>::iterator> MinMaxNode ; 
// maxMemThres, cellRank, nodeRank , locX, locY, velX, velY

/*
 __device__
 SceNodeType indxToType(uint& indx);

 SceNodeType indxToType(uint& indx);
 */

__device__
double CalExtForce(double  curTime);

 __device__
double DefaultMembraneStiff();
//Ali comment 
//__device__
//double calMembrForce(double& length);

//Ali & Abu June 30th 2016  
__device__
double calMembrForce_Mitotic(double& length, double& progress, double mitoticCri, double nodeAdhereIndex);
//Ali Oc 17th 2017
__device__
double calMembrForce_Actin(double& length, double kAvg);


__device__
double CalMembrLinSpringEnergy(double& length, double kAvg);


__device__
double calBendMulti(double& angle, uint activeMembrCt);

//AAMIRI
__device__
double calBendMulti_Mitotic(double& angle, uint activeMembrCt, double& progress, double mitoticCri);

__device__
double CalMembrBendSpringEnergy  (double& angle, uint activeMembrCt, double& progress, double mitoticCri);


__device__
double obtainRandAngle(uint& cellRank, uint& seed);
// comment prevents bad formatting issues of __host__ and __device__ in Nsight

__device__
int obtainRemovingMembrNodeID(uint &cellRank, uint& activeMembrNodes, uint& seed);//AAMIRI
// comment prevents bad formatting issues of __host__ and __device__ in Nsight

__device__
uint obtainMembEndNode(uint &cellRank, uint& activeMembrNodes);//AAMIRI
// comment prevents bad formatting issues of __host__ and __device__ in Nsight

__device__ uint obtainNewIntnlNodeIndex(uint& cellRank, uint& curActiveCount);
// comment prevents bad formatting issues of __host__ and __device__ in Nsight

__device__ uint obtainLastIntnlNodeIndex(uint& cellRank, uint& curActiveCount);//AAMIRI
// comment prevents bad formatting issues of __host__ and __device__ in Nsight

__device__
bool isAllIntnlFilled(uint& currentIntnlCount);
// comment prevents bad formatting issues of __host__ and __device__ in Nsight

__device__
bool isAllIntnlEmptied(uint& currentIntnlCount);//AAMIRI
// comment prevents bad formatting issues of __host__ and __device__ in Nsight

__device__
bool isAllMembrEmptied(uint& currentMembrCount);//AAMIRI
// comment prevents bad formatting issues of __host__ and __device__ in Nsight


__device__
bool longEnough(double& length);

__device__
bool bigEnough(double& num);

__device__
double cross_Z(double vecA_X, double vecA_Y, double vecB_X, double vecB_Y);

// __device__
// void calAndAddIB_M(double& xPos, double& yPos, double& xPos2, double& yPos2,
// 		double& growPro, double& xRes, double& yRes, double grthPrgrCriVal_M);
__device__
void calAndAddIB_M(double& xPos, double& yPos, double& xPos2, double& yPos2,
		double& growPro, double& xRes, double& yRes, double grthPrgrCriVal_M, bool enteringMitotic);
__device__
void CalAndAddIMEnergy(double& xPos, double& yPos, double& xPos2, double& yPos2,
		double& growPro, double& IMEnergyT, double grthPrgrCriVal_M);


//AliA 
// __device__
// void calAndAddIB_M2(double& xPos, double& yPos, double& xPos2, double& yPos2,
// 		double& growPro, double& xRes, double& yRes, double &F_MI_M_x, double & F_MI_M_y,double grthPrgrCriVal_M);
	__device__
void calAndAddIB_M2(double& xPos, double& yPos, double& xPos2, double& yPos2,
		double& growPro, double& xRes, double& yRes, double &F_MI_M_x, double & F_MI_M_y,double grthPrgrCriVal_M, bool enteringMitotic);

// __device__
// void calAndAddMM_ContractAdh(double& xPos, double& yPos, double& xPos2, double& yPos2,
// 			double& xRes, double& yRes, double &F_MM_C_X, double & F_MM_C_Y);
__device__
void calAndAddMM_ContractAdh(double& xPos, double& yPos, double& xPos2, double& yPos2,
			double& xRes, double& yRes, double &F_MM_C_X, double & F_MM_C_Y, double& kContrMemb_multip, double& kContrMemb_multip2);

__device__
void calAndAddMM_ContractRepl(double& xPos, double& yPos, double& xPos2, double& yPos2,
			double& xRes, double& yRes, double &F_MM_C_X, double & F_MM_C_Y);


__device__
void calAndAddII_M(double& xPos, double& yPos, double& xPos2, double& yPos2,
		double& growPro, double& xRes, double& yRes, double grthPrgrCriVal_M);

__device__
void CalAndAddIIEnergy(double& xPos, double& yPos, double& xPos2, double& yPos2,
		double& growPro, double& IIEnergyT, double grthPrgrCriVal_M);
__device__
void calAndAddNucleusEffect(double &  xPos, double & yPos, double & xPos2, double &yPos2, 
		double & growPro, double & xRes, double & yRes,double _grthPrgrCriVal_M);

__device__
double compDist2D(double &xPos, double &yPos, double &xPos2, double &yPos2);

/**
 * Functor for divide operation.
 * @param dividend divisor for divide operator.
 * @param input1: number to be divided
 * @return output: result from division
 */
struct DivideFunctor: public thrust::unary_function<uint, uint> {
	uint dividend;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ DivideFunctor(uint dividendInput) :
			dividend(dividendInput) {
	}
	__host__ __device__ uint operator()(const uint &num) {
		return num / dividend;
	}
};

struct PlusNum: public thrust::unary_function<uint, uint> {
	uint _addNum;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ PlusNum(uint num) :
			_addNum(num) {
	}
	__host__ __device__
	double operator()(const uint &num1) {
		return num1 + _addNum;
	}
};

/**
 * Functor for modulo operation.
 * @param dividend divisor for modulo operator.
 * @param input1: number to be moduled
 * @return output: result from modulo
 */
struct ModuloFunctor: public thrust::unary_function<uint, uint> {
	uint dividend;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ ModuloFunctor(uint dividendInput) :
			dividend(dividendInput) {
	}
	__host__ __device__ uint operator()(const uint &num) {
		return num % dividend;
	}
};

struct isActiveNoneBdry {
	__host__ __device__
	bool operator()(boolType b) {
		bool isActive = thrust::get<0>(b);
		SceNodeType type = thrust::get<1>(b);
		if (isActive && type != Boundary) {
			return true;
		} else {
			return false;
		}
	}
};

// struct MaxWInfo: public thrust::binary_function<DUiDDD, DUiDDD, DUiDDD> {
// 	__host__ __device__ DUiDDD operator()(const DUiDDD& data1,
// 			const DUiDDD& data2) {
// 		double num1 = thrust::get<4>(data1); // choose the max distance not the maximum tension
// 		double num2 = thrust::get<4>(data2);
// 		if (num1 > num2) {
// 			return data1;
// 		} else {
// 			return data2;
// 		}
// 	}
// };

struct MaxWInfo: public thrust::binary_function<DUiDDDT, DUiDDDT, DUiDDDT> {
	__host__ __device__ DUiDDDT operator()(const DUiDDDT& data1,
			const DUiDDDT& data2) {
		double num1 = thrust::get<4>(data1); // choose the max distance not the maximum tension
		double num2 = thrust::get<4>(data2);
		MembraneType1 memnodetype_1 = thrust::get<5>(data1);
		MembraneType1 memnodetype_2 = thrust::get<5>(data2);
		uint indxDump = thrust::get<1>(data1);
		if (memnodetype_1 == lateralA && memnodetype_2 == lateralA){
			return thrust::make_tuple(num1-100000, -indxDump, num1-100000, num1-100000, -10000, notAssigned1);
		}
		else if (memnodetype_1 == lateralA && memnodetype_2 == lateralB){
			return thrust::make_tuple(num1-100000, -indxDump, num1-100000, num1-100000, -20000, notAssigned1);
		} 
		else if (memnodetype_1 == lateralB && memnodetype_2 == lateralB){
			return thrust::make_tuple(num1-100000, -indxDump, num1-100000, num1-100000, -30000, notAssigned1);
		} 
		else if (memnodetype_1 == lateralB && memnodetype_2 == lateralA){
			return thrust::make_tuple(num1-100000, -indxDump, num1-100000, num1-100000, -40000, notAssigned1);
		}
		// else if (memnodetype_1 == notAssigned1 || memnodetype_2 == notAssigned1){
		// 	return thrust::make_tuple(num1-100000, -indxDump, num1-100000, num1-100000, -50000, notAssigned1);
		// }
		else{
			if (memnodetype_1 == lateralA || memnodetype_1 == lateralB || memnodetype_1 == notAssigned1){
				return data2;
			}
			else if (memnodetype_2 == lateralA || memnodetype_2 == lateralB || memnodetype_2 == notAssigned1){
				return data1;
			}
			else if (num1 > num2) {
				return data1; //thrust::make_tuple(thrust::get<0>(data1), thrust::get<1>(data1), thrust::get<2>(data1), thrust::get<3>(data1), thrust::get<4>(data1));
			} else {
				return data2; //thrust::make_tuple(thrust::get<0>(data2), thrust::get<1>(data2), thrust::get<2>(data2), thrust::get<3>(data2), thrust::get<4>(data2));
			}
		}
	}
};

//Ali
struct MinWInfo: public thrust::binary_function<DUi, DUi, DUi> {
	__host__ __device__ DUi operator()(const DUi & data_1,const DUi & data_2) {
		double num1 = thrust::get<0>(data_1);
		double num2 = thrust::get<0>(data_2);
	
		if ( num1 < num2 && num1>0.000001) {  // just a small number
			return data_1;
		} else if (num2>0.000001) {
		    return data_2;
		}
		else {
			return thrust:: make_tuple (num1+10000, thrust::get<1>(data_1)) ;  // we add this number to remove zero from being candidate for minimum value 
		}
	}
};

/**
 * Functor for add two three dimensional vectors.
 * @param input1 first three dimensional vector to add
 * @param input2 second three dimensional vector to add
 * @return output result of addition
 */
struct CVec3Add: public thrust::binary_function<CVec3, CVec3, CVec3> {
	__host__ __device__ CVec3 operator()(const CVec3 &vec1, const CVec3 &vec2) {
		return thrust::make_tuple(thrust::get<0>(vec1) + thrust::get<0>(vec2),
				thrust::get<1>(vec1) + thrust::get<1>(vec2),
				thrust::get<2>(vec1) + thrust::get<2>(vec2));
	}
};

struct CVec2Add: public thrust::binary_function<CVec2, CVec2, CVec2> {
	__host__ __device__ CVec2 operator()(const CVec2 &vec1, const CVec2 &vec2) {
		return thrust::make_tuple(thrust::get<0>(vec1) + thrust::get<0>(vec2),
				thrust::get<1>(vec1) + thrust::get<1>(vec2));
	}
};


/**
 * Divide three inputs by one same number.
 * @param input1 first number to be divide \n
 *        input2 second number to be divide \n
 *        input3 third number to be divide \n
 * @return output1 first division result \n
 *        output2 second division result \n
 *        output3 third division result \n
 */
struct CVec3Divide: public thrust::binary_function<CVec3, double, CVec3> {
	__host__ __device__ CVec3 operator()(const CVec3 &vec1,
			const double &divisor) {
		return thrust::make_tuple(thrust::get<0>(vec1) / divisor,
				thrust::get<1>(vec1) / divisor, thrust::get<2>(vec1) / divisor);
	}
};

struct CVec2Divide: public thrust::binary_function<CVec2, double, CVec2> {
	__host__ __device__ CVec2 operator()(const CVec2 &vec1,
			const double &divisor) {
		return thrust::make_tuple(thrust::get<0>(vec1) / divisor,
				thrust::get<1>(vec1) / divisor);
	}
};

struct LessEqualTo: public thrust::unary_function<UiB, bool> {
	uint _limit;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ LessEqualTo(uint limit) :
			_limit(limit) {
	}
	__device__
	bool operator()(const UiB& numBool) const {
		uint num = thrust::get<0>(numBool);
		uint isGrow = thrust::get<1>(numBool);
		if (num <= _limit && isGrow) {
			return true;
		} else {
			return false;
		}
	}
};

//Ali comment end

//Ali Acin Level
struct ActinLevelCal: public thrust::unary_function<ActinData, double> {
	int _maxNodePerCell;
	bool* _isActiveAddr;
	int* _cellRoot;
	double _minY ; 
	double _maxY ; 
	bool _membPolar ; 
	bool _subMembPolar ; 

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	 __host__  __device__ ActinLevelCal(uint maxNodePerCell, bool* isActiveAddr, int* cellRoot, double minY, double maxY,bool membPolar, bool subMembPolar) :
			 _maxNodePerCell(maxNodePerCell), _isActiveAddr(isActiveAddr),_cellRoot(cellRoot), _minY(minY),_maxY(maxY),_membPolar(membPolar), _subMembPolar(subMembPolar) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	  __device__ double operator()(const ActinData &actinData) const {
		ECellType  cellType= thrust::get<0>(actinData);
		int activeMembrCount = thrust::get<1>(actinData);
		double cell_CenterY = thrust::get<2>(actinData);
		MembraneType1    memType= thrust::get<3>(actinData);
		bool    isSubApical= thrust::get<4>(actinData);
		int   cellRank = thrust::get<5>(actinData);
		int   nodeRank = thrust::get<6>(actinData);

		int  index = cellRank * _maxNodePerCell + nodeRank;
		double actinLevel ;
		double kStiff ; 
	   //MembraneType1  membraneType ; 	
		kStiff=DefaultMembraneStiff() ;  
		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount) {  //if #1
			return 0.0;
		} else { // It is a membrane node    //if #1 continue

			actinLevel=1*kStiff ;  // default

		/*
			if (_membPolar) {  // if # 4 start 
				if (cellType==pouch) {  // if # 5 starts 
                
					actinLevel=0.5*kStiff ;
				}
				else if (cellType==bc) { // if #5 continue 
					
					actinLevel=1*kStiff ;

				}
				else { // means peri  // if # 5 continue 

					actinLevel=2*kStiff ;
				}  // if # 5 ends
			}  // if # 4 ends
		*/			

	//		if (_subMembPolar) { // if # 6 s
				if ( (cellType==pouch && memType==lateralB) || (cellType==pouch && memType==lateralA)  ) { 
					actinLevel=3.0*kStiff ;  //0.5
				}
		        if (cellType==pouch &&  memType==apical1) {
					 actinLevel=3.0*kStiff ; 
				}
				if (cellType==pouch &&  memType==basal1) {
					 actinLevel=3.0*kStiff ; // 0.55
				}

				
				if ( (cellType==peri && memType==lateralB) || (cellType==peri && memType==lateralA)  ) { 
					  actinLevel=3.0*kStiff ;
				}
				if   (cellType==peri && memType == apical1) {
					  actinLevel=3.0*kStiff ;
				}
				if   (cellType==peri && memType == basal1) {
					  actinLevel=3.0*kStiff ;
				}
				

				if ( (cellType==bc && memType==lateralB) || (cellType==bc && memType==lateralA)  ) { 
					actinLevel=3.0*kStiff ; //1.5
				}
		        if (cellType==bc &&  memType==apical1) {
					 actinLevel=3.0*kStiff ; // 1.5
				}
				if (cellType==bc &&  memType==basal1) {
					 actinLevel=3.0*kStiff ;
				}



			    //if   (cellType==bc) {  // bc cell type either apicalbasal or lateral
				//	actinLevel=1*kStiff ;
			//	}
	//		} // if #6 end

		//	if (memType==lateralB) {
		//		actinLevel=7.5*kStiff ;
		//	}

		//	if (memType==lateralA) {
		//		actinLevel=2.0*kStiff ;
		//	}
		//	if (isSubApical) {

					//actinLevel=6.0*kStiff ;
		//	}

		    return actinLevel;

	    } // if 1# ends
}
}; 

struct CalShiftVec: public thrust::unary_function<CVec4,CVec2> {
	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalShiftVec() {
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ CVec2 operator()(const CVec4 &cVec4) const {
		double   internalAvgX= thrust::get<0>(cVec4);
		double   internalAvgY = thrust::get<1>(cVec4);
		double   nucleusX = thrust::get<2>(cVec4);
		double   nucleusY=  thrust::get<3>(cVec4) ;

        
			return thrust::make_tuple(nucleusX-internalAvgX,nucleusY-internalAvgY) ;  
		}
}; 

struct AdjustInternalNodesLoc: public thrust::unary_function<DDUiBDD, CVec2> {
	uint _maxMemNodePerCell;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AdjustInternalNodesLoc(
			uint maxMemNodePerCell) : _maxMemNodePerCell(
					maxMemNodePerCell) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec2 operator()(const DDUiBDD &dDUiBDD) const {
		double shiftX = thrust::get<0>(dDUiBDD);
		double shiftY = thrust::get<1>(dDUiBDD);
		uint nodeRank = thrust::get<2>(dDUiBDD);
		bool isActive =thrust::get<2>(dDUiBDD) ; 
		double locX = thrust::get<4>(dDUiBDD);
		double locY = thrust::get<5>(dDUiBDD);
                

		if (isActive == false || nodeRank<_maxMemNodePerCell) {
			return thrust::make_tuple(locX,locY); //AliE
		}
		else {

			//return thrust::make_tuple(locX+shiftX,locY+shiftY); //AliE
			return thrust::make_tuple(locX,locY); //AliE
		}
			
	}
};





struct CalNucleusLoc: public thrust::unary_function<CVec5,CVec2> {
	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalNucleusLoc() {
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ CVec2 operator()(const CVec5 &cVec5) const {
		double   progress= thrust::get<0>(cVec5);
		double   centerX = thrust::get<1>(cVec5);
		double   centerY = thrust::get<2>(cVec5);
		double   apicalX=  thrust::get<3>(cVec5) ;
		double   apicalY = thrust::get<4>(cVec5);

        double nucleusX,nucleusY ;
		double nucleusHPercent ;
		double pi=3.14159 ; 
		//nucleusHPercent=4*(progress-0.5)*(progress-0.5) ;
		nucleusHPercent=0.5*cos(2*pi*progress) + 0.5  ; // to handle negative progress at the begining
		if (apicalX<0.001 && apicalX>-0.001 && apicalY<0.001 && apicalY>-0.001 ) {  // to check if a double is equal to zero.

			return thrust::make_tuple(centerX,centerY) ; // if there is no apical point put the nucleus on the center. 
		}
		else {
			nucleusX= centerX+nucleusHPercent*(apicalX-centerX)*0.75 ; 
			nucleusY= centerY+nucleusHPercent*(apicalY-centerY)*0.75 ; 

			return thrust::make_tuple( nucleusX,nucleusY) ; 
		}
	}
};

struct CalCellHeight: public thrust::unary_function<CVec7,CVec3> {
	double _distFromNucleus_normalMax1;
	double _distFromNucleus_normalMax2;
	double _distFromNucleus_normalMax3;
	double _distFromNucleus_normalMax_apical1;
	double _distFromNucleus_normalMax_apical2;
	double _distFromNucleus_normalMax_apical3;

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalCellHeight(double distFromNucleus_normalMax1,
										double distFromNucleus_normalMax2,
										double distFromNucleus_normalMax3,
										double distFromNucleus_normalMax_apical1,
										double distFromNucleus_normalMax_apical2,
										double distFromNucleus_normalMax_apical3): 
								_distFromNucleus_normalMax1(distFromNucleus_normalMax1),
								_distFromNucleus_normalMax2(distFromNucleus_normalMax2),
								_distFromNucleus_normalMax3(distFromNucleus_normalMax3),
								_distFromNucleus_normalMax_apical1(distFromNucleus_normalMax_apical1),
								_distFromNucleus_normalMax_apical2(distFromNucleus_normalMax_apical2),
								_distFromNucleus_normalMax_apical3(distFromNucleus_normalMax_apical3) {
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ CVec3 operator()(const CVec7 &cVec7) const {
		uint cellRank = thrust::get<0>(cVec7);
		double   apicalX=  thrust::get<1>(cVec7) ;
		double   apicalY = thrust::get<2>(cVec7);
		double   basalX=  thrust::get<3>(cVec7) ;
		double   basalY = thrust::get<4>(cVec7);
		bool	isEnteringMitotic = thrust::get<5>(cVec7);
		double	individualCellHeightPreMitotic = thrust::get<6>(cVec7);
		//nucleusHPercent=4*(progress-0.5)*(progress-0.5) ;
		double cellHeight, cellHeight_springHeight, cellHeight_springHeight_apical;
		if (1 < 0){//isEnteringMitotic == true){
			// return thrust::make_tuple(individualCellHeightPreMitotic, 0.0, 0.0);
		}
		else{
			cellHeight = sqrt((apicalX - basalX)*(apicalX - basalX) + (apicalY - basalY)*(apicalY - basalY));
			if (cellRank >= 2 && cellRank <= 21){
				cellHeight_springHeight = _distFromNucleus_normalMax1;//-1.0*cellHeight*0.275;
				cellHeight_springHeight_apical = _distFromNucleus_normalMax_apical1;//1.0*cellHeight*0.215;
			}
			if (cellRank >= 22 && cellRank <= 42){
				cellHeight_springHeight = _distFromNucleus_normalMax2;//-1.0*cellHeight*0.275;
				cellHeight_springHeight_apical = _distFromNucleus_normalMax_apical2;//1.0*cellHeight*0.215;
			}
			if (cellRank >= 43 && cellRank <= 64){
				cellHeight_springHeight = _distFromNucleus_normalMax3;//-1.0*cellHeight*0.275;
				cellHeight_springHeight_apical = _distFromNucleus_normalMax_apical3;//1.0*cellHeight*0.215;
			}
			return thrust::make_tuple( cellHeight, cellHeight_springHeight, cellHeight_springHeight_apical) ; 
		}
	}
};

struct CalCellHeight_Ver2: public thrust::unary_function<CVec7,double> {

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalCellHeight_Ver2()  {
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ double operator()(const CVec7 &cVec7) const {
		uint cellRank = thrust::get<0>(cVec7);
		double   apicalX=  thrust::get<1>(cVec7) ;
		double   apicalY = thrust::get<2>(cVec7);
		double   basalX=  thrust::get<3>(cVec7) ;
		double   basalY = thrust::get<4>(cVec7);
		bool	isEnteringMitotic = thrust::get<5>(cVec7);
		double	individualCellHeightPreMitotic = thrust::get<6>(cVec7);
		//nucleusHPercent=4*(progress-0.5)*(progress-0.5) ;
		double cellHeight, cellHeight_springHeight, cellHeight_springHeight_apical;
		if (1 < 0){//isEnteringMitotic == true){
			// return thrust::make_tuple(individualCellHeightPreMitotic, 0.0, 0.0);
		}
		else{
			cellHeight = sqrt((apicalX - basalX)*(apicalX - basalX) + (apicalY - basalY)*(apicalY - basalY));
			return  cellHeight ; 
		}
	}
};

struct CalNucleusDesireLoc: public thrust::unary_function<CVec5,CVec3> {
	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalNucleusDesireLoc() {
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ CVec3 operator()(const CVec5 &cVec5) const {
		double   nucleusHPercent= thrust::get<0>(cVec5);
		double   centerX = 		  thrust::get<1>(cVec5);
		double   centerY =        thrust::get<2>(cVec5);
		double   apicalX=         thrust::get<3>(cVec5);
		double   apicalY =        thrust::get<4>(cVec5);

        double nucleusDesireX,nucleusDesireY ;
		double distance ; 
		if (apicalX<0.001 && apicalX>-0.001 && apicalY<0.001 && apicalY>-0.001 ) {  // to check if a double is equal to zero.
			distance=sqrt( (centerX-apicalX)*(centerX-apicalX)+(centerY-apicalY)*(centerY-apicalY) ) ;  
			return thrust::make_tuple(centerX,centerY,distance) ; // if there is no apical point put the nucleus on the center. 
		}
		else {
			// nucleusDesireX= centerX+(nucleusHPercent-0.5)*(apicalX-centerX) ; 
			// nucleusDesireY= centerY+(nucleusHPercent-0.5)*(apicalY-centerY) ; 
			nucleusDesireX= centerX+(nucleusHPercent-0.6)*(apicalX-centerX) ; 
			nucleusDesireY= centerY+(nucleusHPercent-0.6)*(apicalY-centerY) ; 

			distance=sqrt( (nucleusDesireX-apicalX)*(nucleusDesireX-apicalX)+(nucleusDesireY-apicalY)*(nucleusDesireY-apicalY) ) ;  
			return thrust::make_tuple( nucleusDesireX,nucleusDesireY, distance) ; 
		}
	}
};

struct CalCellCenterPerturbedLoc: public thrust::unary_function<CVec5,CVec3> {
	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalCellCenterPerturbedLoc() {
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ CVec3 operator()(const CVec5 &cVec5) const {
		double   nucleusHPercent= thrust::get<0>(cVec5);
		double   centerX = 		  thrust::get<1>(cVec5);
		double   centerY =        thrust::get<2>(cVec5);
		double   apicalX=         thrust::get<3>(cVec5);
		double   apicalY =        thrust::get<4>(cVec5);

        double nucleusDesireX,nucleusDesireY ;
		double distance ; 
		
			// nucleusDesireX= centerX+(nucleusHPercent-0.5)*(apicalX-centerX) ; 
			// nucleusDesireY= centerY+(nucleusHPercent-0.5)*(apicalY-centerY) ; 
			nucleusDesireX= centerX+(nucleusHPercent-0.6); 
			nucleusDesireY= centerY+(nucleusHPercent-0.6); 

			distance=sqrt( (nucleusDesireX-apicalX)*(nucleusDesireX-apicalX)+(nucleusDesireY-apicalY)*(nucleusDesireY-apicalY) ) ;  
			return thrust::make_tuple( nucleusDesireX,nucleusDesireY, distance) ; 
		
	}
};





struct CalNucleusIniLocPercent: public thrust::unary_function<CVec3,double> {
	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalNucleusIniLocPercent() {
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ double  operator()(const CVec3 &cVec3) const {
		double   avgPosY= thrust::get<0>(cVec3);
		double   centerY = thrust::get<1>(cVec3);
		double   apicalY = thrust::get<2>(cVec3);

			return ( 0.5*( (avgPosY-centerY)/(apicalY-centerY) ) + 0.5 ) ; 
		}
}; 

struct ApicalLocCal: public thrust::unary_function<CVec2Int,CVec2> {
	int * _apicalNodeCountAddr ; 	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ ApicalLocCal(int * apicalNodeCountAddr): _apicalNodeCountAddr(apicalNodeCountAddr){
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ CVec2 operator()(const CVec2Int &cVec2Int) const {
		double   apicalX=  thrust::get<0>(cVec2Int) ;
		double   apicalY = thrust::get<1>(cVec2Int);
		uint      cellRank = thrust::get<2>(cVec2Int);

     //   if (_apicalNodeCount[cellRank]>0) {
         
			return thrust::make_tuple( apicalX/_apicalNodeCountAddr[cellRank],
									   apicalY/_apicalNodeCountAddr[cellRank] ) ; 
	//	}
	//	else {

	//		return thrust::make_tuple(0,0) ; // there is no apical node 
	//	}


	}
}; 

//Ali 
struct BasalLocCal: public thrust::unary_function<CVec2Int,CVec2> {
	int * _basalNodeCountAddr ; 	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ BasalLocCal(int * basalNodeCountAddr): _basalNodeCountAddr(basalNodeCountAddr){
		
		}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ CVec2 operator()(const CVec2Int &cVec2Int) const {
		double   basalX=  thrust::get<0>(cVec2Int) ;
		double   basalY = thrust::get<1>(cVec2Int);
		uint      cellRank = thrust::get<2>(cVec2Int);

         
			return thrust::make_tuple( basalX/_basalNodeCountAddr[cellRank],
									   basalY/_basalNodeCountAddr[cellRank] ) ; 

	}
}; 






struct AssignMemNodeType: public thrust::unary_function<BTUiUi, TII> {
	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AssignMemNodeType(){
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__  __device__ TII  operator()(const BTUiUi &bTUiUi) const {
		bool            isActive=  thrust::get<0>(bTUiUi) ; 
		MembraneType1   nodeType= thrust::get<1>(bTUiUi); 
		uint            nodeRank = thrust::get<2>(bTUiUi) ; // node rank in each cell 
		uint            activeMembrCount = thrust::get<3>(bTUiUi) ; 
/*
		if (isActive == false || nodeRank >= activeMembrCount) { 
			return thrust::make_tuple(notAssigned1,0);
		} else if(nodeType==lateral1) { 
			return thrust::make_tuple( lateral1,0) ; 
		}
			else if (nodeType==basal1) {
				return thrust::make_tuple(basal1,0) ; 
			}
				else {
					return thrust::make_tuple(apical1,1) ; 
		}
*/

		if(nodeType==apical1) { 
			return thrust::make_tuple( nodeType,1,0) ;
		}

		else if (nodeType==basal1) {

			return thrust::make_tuple( nodeType,0,1) ;
		}
		else {
			return thrust::make_tuple( nodeType,0,0) ;

		}
		/*
		if (isActive == false || nodeRank >= activeMembrCount) { 
			return thrust::make_tuple(notAssigned1,0);
		} else if(nodeType==apical1) { 
			return thrust::make_tuple( apical1,1) ; 
			}
			else if (nodeType==basal1) {
				return thrust::make_tuple(basal1,0) ; 
				}
				else {
					return thrust::make_tuple(lateral1,0) ; 
		}
		*/
	}

}; 







//Ali  //ChangesMadeByKT
struct AddMembrForce: public thrust::unary_function<TensionData_type2, CVec10> {
	uint _bdryCount;
	uint _maxNodePerCell;
	double* _locXAddr;
	double* _locYAddr;
	bool* _isActiveAddr;
	int* _adhereIndexAddr;
	double* _actinLevelAddr;
	double _mitoticCri;
	double _minY ; 
	double _maxY ; 
	int* _cellSubdomainIndx;

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddMembrForce(uint bdryCount, uint maxNodePerCell,
			double* locXAddr, double* locYAddr, bool* isActiveAddr, int* adhereIndexAddr,double *actinLevelAddr, double mitoticCri, double minY, double maxY, int* cellSubdomainIndx) :
			_bdryCount(bdryCount), _maxNodePerCell(maxNodePerCell), _locXAddr(
					locXAddr), _locYAddr(locYAddr), _isActiveAddr(isActiveAddr),_adhereIndexAddr(adhereIndexAddr),_actinLevelAddr(actinLevelAddr), _mitoticCri(mitoticCri),_minY(minY),_maxY(maxY), _cellSubdomainIndx(cellSubdomainIndx) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec10 operator()(const TensionData_type2 &tData2) const {

		double progress = thrust::get<0>(tData2);
		uint activeMembrCount = thrust::get<1>(tData2);
		// double cell_CenterY = thrust::get<2>(tData);
		MembraneType1  memType= thrust::get<2>(tData2);
		int    adhereIndex= thrust::get<3>(tData2);
		uint   cellRank = thrust::get<4>(tData2);
		uint   nodeRank = thrust::get<5>(tData2);
		double locX = thrust::get<6>(tData2);
		double locY = thrust::get<7>(tData2);
		double velX = thrust::get<8>(tData2);
		double velY = thrust::get<9>(tData2);

		uint index = _bdryCount + cellRank * _maxNodePerCell + nodeRank;

		double mag = 0;
		double rightMag = 0;
		double midX = 0;
		double midY = 0;
		double bendLeftX = 0;
		double bendLeftY = 0;
		double bendRightX = 0;
		double bendRightY = 0;

		double leftPosX;
		double leftPosY;
		double leftDiffX;
		double leftDiffY;
		double lenLeft;

		double rightPosX;
		double rightPosY;
		double rightDiffX;
		double rightDiffY;
		double lenRight;
        double kAvgRight,kAvgLeft ; 		

		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount) {
			return thrust::make_tuple(velX, velY, mag, rightMag, midX, midY,
					bendLeftX, bendLeftY, bendRightX, bendRightY);
		} else {
			int index_left = nodeRank - 1;
			if (index_left == -1) {
				index_left = activeMembrCount - 1;
			}
			index_left = index_left + _bdryCount + cellRank * _maxNodePerCell;
			// apply tension force from left
			if (_isActiveAddr[index_left]) {
				leftPosX = _locXAddr[index_left];
				leftPosY = _locYAddr[index_left];
				kAvgLeft=0.5*(_actinLevelAddr[index_left]+_actinLevelAddr[index]); 
				//kAvgLeft=_actinLevelAddr[index]; 
				leftDiffX = leftPosX - locX;
				leftDiffY = leftPosY - locY;
				lenLeft = sqrt(leftDiffX * leftDiffX + leftDiffY * leftDiffY);
				//double forceVal = calMembrForce_Mitotic(lenLeft,progress, _mitoticCri,adhereIndex); //Ali & Abu June 30th
				double forceVal =calMembrForce_Actin(lenLeft,kAvgLeft); // Ali & June 30th
				//ChangesMadeByKT_begin
				if (_cellSubdomainIndx[cellRank] == 0){
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 1){
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 2){
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}
				else{
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}//ChangesMadeByKT_end
			        
			        //if (adhereIndex==-1 && _adhereIndexAddr[index_left]==-1) {
				if (longEnough(lenLeft)) {
					velX = velX + forceVal * leftDiffX / lenLeft;
					velY = velY + forceVal * leftDiffY / lenLeft;
					mag = forceVal + mag;
				}
			}

			int index_right = nodeRank + 1;
			if (index_right == (int) activeMembrCount) {
				index_right = 0;
			}
			index_right = index_right + _bdryCount + cellRank * _maxNodePerCell;
			// apply tension force from right
			if (_isActiveAddr[index_right]) {
				rightPosX = _locXAddr[index_right];
				rightPosY = _locYAddr[index_right];
				kAvgRight=0.5*(_actinLevelAddr[index_right]+_actinLevelAddr[index]); 
				//kAvgRight=_actinLevelAddr[index]; 
				rightDiffX = rightPosX - locX;
				rightDiffY = rightPosY - locY;
				lenRight = sqrt(
						rightDiffX * rightDiffX + rightDiffY * rightDiffY);
				//double forceVal = calMembrForce_Mitotic(lenRight,progress, _mitoticCri,adhereIndex); // Ali & June 30th
				double forceVal = calMembrForce_Actin(lenRight,kAvgRight); // Ali & June 30th
				//ChangesMadeByKT_begin
				if (_cellSubdomainIndx[cellRank] == 0){
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 1){
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 2){
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}
				else{
					if (memType == lateralA ){
						forceVal = forceVal;
					}
					else if (memType == lateralB){
						forceVal = forceVal;
					}
					else if (memType == apical1){
						forceVal = forceVal;
					}
					else if (memType == basal1){
						forceVal = forceVal;
					}
				}//ChangesMadeByKT_end

				//if (adhereIndex==-1 && _adhereIndexAddr[index_right]==-1) {
			if (longEnough(lenRight)) {
					velX = velX + forceVal * rightDiffX / lenRight;
					velY = velY + forceVal * rightDiffY / lenRight;
					mag = forceVal + mag;
					rightMag = forceVal;
					midX = (rightPosX + locX) / 2;
					midY = (rightPosY + locY) / 2;
				}
			}
			// applies bending force.
			if (_isActiveAddr[index_left] && _isActiveAddr[index_right]) {
				if (longEnough(lenLeft) && longEnough(lenRight)) {
					double dotP = -leftDiffX * rightDiffX
							- leftDiffY * rightDiffY;
					double vecP = dotP / (lenLeft * lenRight);

					// because of numerical error, 1 - vecP*vecP could be less than 0, although it is not possible in mathematics.
					// sqrt(negative number) would cause term0 to be nan.
					// if an nan number is produced, it will not be accepted by bigEnough function.
					// this is OK, because we know at that time bending energy should be 0.
					double term0 = sqrt(1 - vecP * vecP);
					// this if statement is required for numerical purpose only.
					// Whole term would go to zero when term 0 close to zero, but the computation
					// would cause numerical errors, so need to make sure term0 is big enough.
					if (bigEnough(term0)) {
						double angle;
						// value of cross product in z direction: vecA_X * vecB_Y - vecA_Y * vecB_X
						double crossZ = leftDiffY * rightDiffX
								- leftDiffX * rightDiffY;
						if (crossZ > 0) {
							// means angle > PI (concave)
							angle = PI + acos(vecP);
						} else {
							// means angle < PI (convex)
							angle = PI - acos(vecP);
						}
						// leftDiffX = ax-bx
						// rightDiffX = cx-bx
						double term1x = -rightDiffX / (lenLeft * lenRight);
						double term2x = leftDiffX / (lenLeft * lenRight);
						double term3x = (dotP * leftDiffX)
								/ (lenLeft * lenLeft * lenLeft * lenRight);
						double term4x = (-dotP * rightDiffX)
								/ (lenLeft * lenRight * lenRight * lenRight);
						double term1y = -rightDiffY / (lenLeft * lenRight);
						double term2y = leftDiffY / (lenLeft * lenRight);
						double term3y = (dotP * leftDiffY)
								/ (lenLeft * lenLeft * lenLeft * lenRight);
						double term4y = (-dotP * rightDiffY)
								/ (lenLeft * lenRight * lenRight * lenRight);

						double bendMultiplier = -calBendMulti_Mitotic(angle,activeMembrCount, progress, _mitoticCri);//AAMIRI modified the arguments
						// because sign of angle formula would change if crossZ < 0
						if (crossZ > 0) {
							bendMultiplier = -bendMultiplier;
						}

						// following are values obtained from matlab: (derivative of angle to each coordinate:
						//-((bx - cx)/(Lab*Lbc) - (DotP*(2*ax - 2*bx))/(2*Lab^3*Lbc))/(1 - DotP^2/(Lab^2*Lbc^2))^(1/2)
						//-((ax - 2*bx + cx)/(Lab*Lbc) + (DotP*(2*ax - 2*bx))/(2*Lab^3*Lbc) - (DotP*(2*bx - 2*cx))/(2*Lab*Lbc^3))/(1 - DotP^2/(Lab^2*Lbc^2))^(1/2)
						//((ax - bx)/(Lab*Lbc) - (DotP*(2*bx - 2*cx))/(2*Lab*Lbc^3))/(1 - DotP^2/(Lab^2*Lbc^2))^(1/2)
						//-((by - cy)/(Lab*Lbc) - (DotP*(2*ay - 2*by))/(2*Lab^3*Lbc))/(1 - DotP^2/(Lab^2*Lbc^2))^(1/2)
						//-((ay - 2*by + cy)/(Lab*Lbc) + (DotP*(2*ay - 2*by))/(2*Lab^3*Lbc) - (DotP*(2*by - 2*cy))/(2*Lab*Lbc^3))/(1 - DotP^2/(Lab^2*Lbc^2))^(1/2)
						//((ay - by)/(Lab*Lbc) - (DotP*(2*by - 2*cy))/(2*Lab*Lbc^3))/(1 - DotP^2/(Lab^2*Lbc^2))^(1/2)

						// f = -dE/dx, so the values added below are negative, compared with the symbolics shown above.
						bendLeftX = bendMultiplier * (term1x - term3x) / term0;
                        velX = velX
								+ bendMultiplier
										* (term2x - term1x + term3x - term4x)
										/ term0 ;                                   
						
						bendRightX = bendMultiplier * (term4x - term2x) / term0;

						bendLeftY = bendMultiplier * (term1y - term3y) / term0;

						velY = velY
								+ bendMultiplier
										* (term2y - term1y + term3y - term4y)
										/ term0;

						bendRightY = bendMultiplier * (term4y - term2y) / term0;

					}
				}
			}
			return thrust::make_tuple(velX, velY, mag, rightMag, midX, midY,
					bendLeftX, bendLeftY, bendRightX, bendRightY);
		}
	}
};

struct CalMembrEnergy: public thrust::unary_function<DUiUiUiDD, CVec2> {
	uint _maxNodePerCell;
	double* _locXAddr;
	double* _locYAddr;
	bool* _isActiveAddr;
	double* _actinLevelAddr;
	double _mitoticCri;
	int* _cellSubdomainIndx;
	//ChangesMadeByKT2_begin
	__host__ __device__ CalMembrEnergy (uint maxNodePerCell,double* locXAddr, double* locYAddr, bool* isActiveAddr, double *actinLevelAddr, double mitoticCri, int* cellSubdomainIndx ) :
			 _maxNodePerCell(maxNodePerCell), _locXAddr(locXAddr), _locYAddr(locYAddr), _isActiveAddr(isActiveAddr),
			 _actinLevelAddr(actinLevelAddr), _mitoticCri(mitoticCri), _cellSubdomainIndx(cellSubdomainIndx) {
	}
	//ChangesMadeByKT2_end
	__device__ CVec2 operator()(const DUiUiUiDDT & dUiUiUiDDT) const {

		double progress = thrust::get<0>(dUiUiUiDDT);
		uint activeMembrCount = thrust::get<1>(dUiUiUiDDT);
		uint   cellRank = thrust::get<2>(dUiUiUiDDT);
		uint   nodeRank = thrust::get<3>(dUiUiUiDDT);
		double locX = thrust::get<4>(dUiUiUiDDT);
		double locY = thrust::get<5>(dUiUiUiDDT);
		MembraneType1	memType = thrust::get<6>(dUiUiUiDDT);


		uint index =  cellRank * _maxNodePerCell + nodeRank;
		double lenLeft,lenRight;
        double kAvgRight,kAvgLeft ; 		
		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount) {
			return thrust::make_tuple(0.0,0.0);
		} else {
			int index_left = nodeRank - 1;
			if (index_left == -1) {
				index_left = activeMembrCount - 1;
			}
			index_left = index_left + cellRank * _maxNodePerCell;

			kAvgLeft=0.5*(_actinLevelAddr[index_left]+_actinLevelAddr[index]); 
			lenLeft = sqrt( ( _locXAddr[index_left] - locX) *( _locXAddr[index_left] - locX) +
			                ( _locYAddr[index_left] - locY) *(_locYAddr[index_left]  - locY)  );
			double energyLinSpringLeft = CalMembrLinSpringEnergy(lenLeft,kAvgLeft);
			//ChangesMadeByKT_begin
				if (_cellSubdomainIndx[cellRank] == 0){
					if (memType == lateralA ){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == lateralB){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == apical1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == basal1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 1){
					if (memType == lateralA ){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == lateralB){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == apical1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == basal1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 2){
					if (memType == lateralA ){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == lateralB){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == apical1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == basal1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
				}
				else{
					if (memType == lateralA ){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == lateralB){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == apical1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
					else if (memType == basal1){
						energyLinSpringLeft = energyLinSpringLeft;
					}
				}//ChangesMadeByKT_end
			int index_right = nodeRank + 1;
			if (index_right == (int) activeMembrCount) {
				index_right = 0;
			}
			index_right = index_right+ cellRank * _maxNodePerCell;

			kAvgRight=0.5*(_actinLevelAddr[index_right]+_actinLevelAddr[index]); 
			lenRight = sqrt( (_locXAddr[index_right] - locX)*(_locXAddr[index_right] - locX)+
					 		 (_locYAddr[index_right] - locY)*(_locYAddr[index_right] - locY) );
			double energyLinSpringRight = CalMembrLinSpringEnergy (lenRight,kAvgRight); // Ali & June 30th
			//ChangesMadeByKT_begin
				if (_cellSubdomainIndx[cellRank] == 0){
					if (memType == lateralA ){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == lateralB){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == apical1){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == basal1){
						energyLinSpringRight = energyLinSpringRight;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 1){
					if (memType == lateralA ){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == lateralB){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == apical1){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == basal1){
						energyLinSpringRight = energyLinSpringRight;
					}
				}
				else if (_cellSubdomainIndx[cellRank] == 2){
					if (memType == lateralA ){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == lateralB){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == apical1){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == basal1){
						energyLinSpringRight = energyLinSpringRight;
					}
				}
				else{
					if (memType == lateralA ){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == lateralB){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == apical1){
						energyLinSpringRight = energyLinSpringRight;
					}
					else if (memType == basal1){
						energyLinSpringRight = energyLinSpringRight;
					}
				}//ChangesMadeByKT_end
			double leftDiffX  = _locXAddr[index_left]   -  locX;
			double leftDiffY  = _locYAddr[index_left]  -   locY;
			double rightDiffX = _locXAddr[index_right]  -  locX;
			double rightDiffY = _locYAddr[index_right]  -  locY;
			double dotP = -leftDiffX * rightDiffX -leftDiffY * rightDiffY;
			double vecP = dotP / (lenLeft * lenRight);
			double angle;
						// value of cross product in z direction: vecA_X * vecB_Y - vecA_Y * vecB_X
			double crossZ = leftDiffY * rightDiffX - leftDiffX * rightDiffY;
						if (crossZ > 0) {
							// means angle > PI (concave)
							angle = PI + acos(vecP);
						} else {
							// means angle < PI (convex)
							angle = PI - acos(vecP);
						}
						
			double energyBendSpring = CalMembrBendSpringEnergy(angle,activeMembrCount, progress, _mitoticCri);
					
			return thrust::make_tuple(energyLinSpringRight+energyLinSpringLeft, energyBendSpring);
		}
   }
};







struct AddExtForces: public thrust::unary_function<TDD, CVec4> {

	double _curTime ; 

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddExtForces(double curTime) :
			_curTime(curTime) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec4 operator()(const TDD &tDD) const {

		MembraneType1 memNodeType = thrust::get<0>(tDD);
		double velX = thrust::get<1>(tDD);
		double velY = thrust::get<2>(tDD);
		double tranT=500 ;
		double fX=0 ; 
		double fY=0 ;
		if (memNodeType==basal1)  {
			fX=CalExtForce(max(_curTime-tranT,0.0)) ;
			velY=0 ; //gripping handles for stretch test won't allow motion in y direction 
		}
		if (memNodeType==apical1) {
			fX= -CalExtForce(max(_curTime-tranT,0.0))  ; 
			velY=0 ; //gripping handles for stretch test won't allow motion in y direction 
		}
		return thrust::make_tuple(velX+fX, velY+fY,fX,fY);
		}
}; 




struct AddLagrangeForces: public thrust::unary_function<DUiDDUiUiDDDD, CVec5> {
	uint _maxNodePerCell;
	double* _locXAddr;
	double* _locYAddr;
	bool* _isActiveAddr;
	double* _cellAreaVecAddr ; 
	double _mitoticCri;
	ECellType*  _cellTypeAddr ; 
	double _timeRatio;
	double _volume_Increase_Target_Ratio;
	bool* _isEnteringMitotic;
	double* _cellAreaGrowthProgress;
	double* _cellAreaGrowthProgressNonMitotic;
	

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddLagrangeForces(uint maxNodePerCell,
			double* locXAddr, double* locYAddr, bool* isActiveAddr, double* cellAreaVecAddr, double mitoticCri, ECellType* cellTypeAddr, double timeRatio, double volume_Increase_Target_Ratio,
			bool* isEnteringMitotic, double* cellAreaGrowthProgress, double* cellAreaGrowthProgressNonMitotic) :
			 _maxNodePerCell(maxNodePerCell), _locXAddr(
					locXAddr), _locYAddr(locYAddr), _isActiveAddr(isActiveAddr),
					_cellAreaVecAddr(cellAreaVecAddr), _mitoticCri(mitoticCri), _cellTypeAddr (cellTypeAddr), _timeRatio(timeRatio),  _volume_Increase_Target_Ratio(volume_Increase_Target_Ratio),
					_isEnteringMitotic(isEnteringMitotic), _cellAreaGrowthProgress(cellAreaGrowthProgress), _cellAreaGrowthProgressNonMitotic(cellAreaGrowthProgressNonMitotic) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec5 operator()(const DUiDDUiUiDDDD &dUiDDUiUiDDDD) const {

		double progress = thrust::get<0>(dUiDDUiUiDDDD);
		uint   activeMembrCount= thrust::get<1>(dUiDDUiUiDDDD);
		double cellCenterX =thrust::get<2>(dUiDDUiUiDDDD);
		double cellCenterY =thrust::get<3>(dUiDDUiUiDDDD);
		uint   cellRank = thrust::get<4>(dUiDDUiUiDDDD);
		uint   nodeRank = thrust::get<5>(dUiDDUiUiDDDD);
		double locX = thrust::get<6>(dUiDDUiUiDDDD);
		double locY = thrust::get<7>(dUiDDUiUiDDDD);
		double velX = thrust::get<8>(dUiDDUiUiDDDD);
		double velY = thrust::get<9>(dUiDDUiUiDDDD);

		uint index = cellRank * _maxNodePerCell + nodeRank;

		double kStiffArea=30 ;       //0.015 ;
		// double kStiffArea=0 ;       //0.015 ;
		double cellAreaDesire ; 
		double posX;
		double posY;
		double len; 

		double posXL;
		double posYL;
		double lenL;

		double posXR;
		double posYR;
		double lenR;
		double fX=0 ; 
		double fY=0 ; 
		double fN=0 ; 


		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount) {
			return thrust::make_tuple(velX, velY,fX,fY,fN);
		} else {

			posX=locX-cellCenterX ; 
			posY=locY-cellCenterY ; 
			len = sqrt(posX * posX + posY * posY);

			int index_left = nodeRank - 1;
			if (index_left == -1) {
				index_left = activeMembrCount - 1;
			}
			index_left = index_left + cellRank * _maxNodePerCell;

			posXL = _locXAddr[index_left]-cellCenterX;
			posYL = _locYAddr[index_left]-cellCenterY ; 
			lenL = sqrt(posXL * posXL + posYL * posYL);
				
			

			int index_right = nodeRank + 1;
			if (index_right == (int) activeMembrCount) {
				index_right = 0;
			}
			index_right = index_right + cellRank * _maxNodePerCell;
			posXR = _locXAddr[index_right]-cellCenterX;
			posYR = _locYAddr[index_right]-cellCenterY;
			lenR = sqrt(posXR * posXR + posYR * posYR);
				
				
	   		/*	
			double term1X = lenL*lenL*posX ;
			double term1Y = lenL*lenL*posY ;

			double term2X=posX*posXL*posXL+posXL*posY*posYL ; 
			double term2Y=posY*posYL*posYL+posYL*posX*posXL ; 

			double term3X=lenR*lenR*posX ; 
			double term3Y=lenR*lenR*posY ; 

			double term4X=posX*posXR*posXR+ posXR*posY*posYR ;
			double term4Y=posY*posYR*posYR+ posYR*posX*posXR ;

			double term5=2*sqrt( pow(len*lenL,2)-pow(posX*posXL+posY*posYL, 2) ) ; 
			double term6=2*sqrt( pow(len*lenR,2)-pow(posX*posXR+posY*posYR, 2) ) ; 
			*/
			double percent ; 
			// int cellRank_division2;
			// if (_cycle == 0){
			// 	cellRank_division2 = 86;
			// }
			// else if (_cycle == 1){
			// 	cellRank_division2 = 87;
			// }

			if (progress>_mitoticCri) {
				percent =(progress-_mitoticCri)/(1.0-_mitoticCri) ;  
			}
			else {
				percent =0 ; // max ((progress-_mitoticCri)/(0.9-_mitoticCri),0.0);  
			}
			
			//ChangesMadeByJRA_begin
			int cellIdDiff;
			//ChangesMadeByJRA_end

			if (_cellTypeAddr[cellRank]==bc) {
				cellAreaDesire=20+ percent*20 ;      //Target cell volume for the cuboidal/boundary cells
			}
			//ChangesMadeByJRA_begin
			else if (cellRank==0 || cellRank==64) {
				//cellAreaDesire=25+ percent*25 ;
		//		cellAreaDesire=65+ percent*65 ;
				cellAreaDesire = 45;                 //Target cell volume for cells 0 and 64 of the columnar cells (start and end of columnar epithelia)
			}
			else if (cellRank==1 || cellRank==63) {
				//cellAreaDesire=50+ percent*50 ;
				cellAreaDesire = 45;                //Target cell volume for cells 0 and 64 of the columnar cells (start and end of columnar epithelia)
			}
			//ChangesMadeByJRA_end
			// else if (cellRank==_cellRank_division && _timeRatio <= _timeRatio_Crit_Division){
			else if (_isEnteringMitotic[cellRank] == true){
				cellAreaDesire=_cellAreaVecAddr[cellRank] + _cellAreaGrowthProgress[cellRank];
				// We assume the volume increase rate is doubled for now
				if (cellAreaDesire >= 65*_volume_Increase_Target_Ratio){
					cellAreaDesire = 65*_volume_Increase_Target_Ratio;
				}
				//65*1.5 would lead to nodes intersecting each other at relaxation step size of 2e-3
				//65*1.25 would not lead to nodes intersecting each other at relaxation step size of 2e-3
			}
			// else if ((cellRank==_cellRank_division || cellRank==cellRank_division2) && _timeRatio > _timeRatio_Crit_Division){
			// else if ((cellRank==_cellRank_division) && _timeRatio > _timeRatio_Crit_Division){
			// 	double targetCellVolume = 65.0;
			// 	// cellAreaDesire=(65*_volume_Increase_Target_Ratio)/2.0;
			// 		// cellAreaDesire=(65*_volume_Increase_Target_Ratio/2.0) + (65 - (65*_volume_Increase_Target_Ratio/2.0))*_postDivision_restorationRateScale*_volume_Increase_Scale*(_timeRatio - _timeRatio_Crit_Division )/(1.0 - _timeRatio_Crit_Division);
			// 	cellAreaDesire=(_cellAreaVecAddr[cellRank]) + (targetCellVolume - _cellAreaVecAddr[cellRank])*_postDivision_restorationRateScale*(_timeRatio - _timeRatio_Crit_Division )/(1.0 - _timeRatio_Crit_Division);
			// }
			// else if ((cellRank == _cellRank_division2) && _timeRatio > _timeRatio_Crit_Division){
			// 	double targetCellVolume = 65.0;
			// 	// cellAreaDesire=(65*_volume_Increase_Target_Ratio)/2.0;
			// 		// cellAreaDesire=(65*_volume_Increase_Target_Ratio/2.0) + (65 - (65*_volume_Increase_Target_Ratio/2.0))*_postDivision_restorationRateScale*_volume_Increase_Scale*(_timeRatio - _timeRatio_Crit_Division )/(1.0 - _timeRatio_Crit_Division);
			// 	cellAreaDesire=(_cellAreaVecAddr[cellRank]) + (targetCellVolume - _cellAreaVecAddr[cellRank])*_postDivision_restorationRateScale*(_timeRatio - _timeRatio_Crit_Division )/(1.0 - _timeRatio_Crit_Division);
			// }
			else {
				// double targetCellVolume = _cellAreaVecAddr[cellRank]*1000;
				// if (targetCellVolume >= 65){
				// 	targetCellVolume = 65;
				// }
				//ChangesMadeByJRA_begin
				/*if (_cellAreaVecAddr[cellRank] <= 65.0){
					cellAreaDesire=(_cellAreaVecAddr[cellRank]) + _cellAreaGrowthProgressNonMitotic[cellRank];
					if (cellAreaDesire >= 65){
						cellAreaDesire = 65.0;
					}
				}
				else if (_cellAreaVecAddr[cellRank] > 65.0){
					cellAreaDesire=(_cellAreaVecAddr[cellRank]) - _cellAreaGrowthProgressNonMitotic[cellRank];
					if (cellAreaDesire <= 65){
						cellAreaDesire = 65.0;
					}
				} */
				//ChangesMadeByJRA_end
				// cellAreaDesire=65+ percent*65 ;
				
				//ChangesMadeByJRA_begin
				//Target volume for the peripodial cells
				if (_cellTypeAddr[cellRank]==peri){
					if (_cellAreaVecAddr[cellRank] <= 65.0){
						cellAreaDesire=(_cellAreaVecAddr[cellRank]) + _cellAreaGrowthProgressNonMitotic[cellRank];
						if (cellAreaDesire >= 65){
							cellAreaDesire = 65.0;
						}
					}
					else if (_cellAreaVecAddr[cellRank] > 65.0){
						cellAreaDesire=(_cellAreaVecAddr[cellRank]) - _cellAreaGrowthProgressNonMitotic[cellRank];
						if (cellAreaDesire <= 65){
							cellAreaDesire = 65.0;
						}
					}
				}
				//Now assign the target volume of columnar cells based on a step function
				//cells 1-20 have target volume = 45
				//cells 21-43 have target volume = 65
				//cells 44-64 have target volume = 45
				else if(cellRank >= 2 && cellRank <=20){
					cellAreaDesire = 45;
				}
				else if(cellRank >= 21 && cellRank <= 43){
					cellAreaDesire = 65;
				}
				else if(cellRank >= 44 && cellRank <= 62){
					cellAreaDesire = 45;
				}

				//We can also use a step function where we split the columnar cells into 5 sections:
				//cells 1-12 have target volume = 45
				//cells 13-25 have target volume = 50
				//cells 26-38 have target volume = 65
				//cells 39-51 have target volume = 50
				//cells 52-64 have target volume = 45
	/* 			else if(cellRank >= 2 && cellRank <=12){
					cellAreaDesire = 45;
				}
				else if(cellRank >= 13 && cellRank <=25){
					cellAreaDesire = 50;
				}
				else if(cellRank >= 26 && cellRank <= 38){
					cellAreaDesire = 65;
				}
				else if(cellRank >= 39 && cellRank <=51){
					cellAreaDesire = 50;
				}
				else if(cellRank >= 52 && cellRank <= 62){
					cellAreaDesire = 45;
				} */

				//ChangesMadeByJRA_end

			}
			
/*
			 fX=-2*kStiffArea*(_cellAreaVecAddr[cellRank]-cellAreaDesire)*
			     ( (term1X-term2X)/term5+ (term3X-term4X)/term6 ) ; 
			 fY=-2*kStiffArea*(_cellAreaVecAddr[cellRank]-cellAreaDesire)*
			     ( (term1Y-term2Y)/term5+ (term3Y-term4Y)/term6 ) ; 
*/
			// cellAreaDesire=75 ; for single cell testing 
			 fX=-2*kStiffArea*(_cellAreaVecAddr[cellRank]-cellAreaDesire)*
			     (  posYR-posYL ) ; 
			 fY=-2*kStiffArea*(_cellAreaVecAddr[cellRank]-cellAreaDesire)*
			     ( -posXR+posXL ) ;
			 fN=-2*kStiffArea*(_cellAreaVecAddr[cellRank]-cellAreaDesire)*sqrt( (posYR-posYL)*(posYR-posYL) +( -posXR+posXL )* ( -posXR+posXL ) ) ;  

		 
			velX=velX+fX ;
			velY=velY+fY ;



			return thrust::make_tuple(velX, velY,fX,fY,fN);
		}
	}
}; 

struct AddContractileRingForces: public thrust::unary_function<DIIUiUiDD, CVec2> {
	uint _maxNodePerCell;
	double* _locXAddr;
	double* _locYAddr;
	double _mitoticCri;

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddContractileRingForces(uint maxNodePerCell,
			double* locXAddr, double* locYAddr, double mitoticCri) :
			 _maxNodePerCell(maxNodePerCell), _locXAddr(
					locXAddr), _locYAddr(locYAddr), _mitoticCri(mitoticCri) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec2 operator()(const DIIUiUiDD &dIIUiUiDD) const {

		double progress = thrust::get<0>(dIIUiUiDD);
		int cellLocalApicalId = thrust::get<1>(dIIUiUiDD);
		int cellLocalBasalId = thrust::get<2>(dIIUiUiDD);
		uint   cellRank = thrust::get<3>(dIIUiUiDD);
		uint   nodeRank = thrust::get<4>(dIIUiUiDD);
		double velX = thrust::get<5>(dIIUiUiDD);
		double velY = thrust::get<6>(dIIUiUiDD);

		int index = cellRank * _maxNodePerCell + nodeRank;
		int cellGlobalApicalId=cellRank * _maxNodePerCell+ cellLocalApicalId ; 
		int cellGlobalBasalId =cellRank * _maxNodePerCell+ cellLocalBasalId ; 
		double kContract=0 ; //10 ;
		double fX= 0 ; 
		double fY=0 ; 

		if ( (index != cellGlobalApicalId && index !=cellGlobalBasalId) || progress< _mitoticCri) {
			return thrust::make_tuple(velX, velY);
		} else
		{
			if ( index==cellGlobalApicalId) {			
				fX=kContract*( _locXAddr[cellGlobalBasalId]-_locXAddr[index]) ; 
				fY=kContract*( _locYAddr[cellGlobalBasalId]-_locYAddr[index]) ;

			}
			else {
				fX=kContract*(_locXAddr[cellGlobalApicalId]-_locXAddr[index])  ; 
				fY=kContract*( _locYAddr[cellGlobalApicalId]-_locYAddr[index])  ;

			}
			return thrust::make_tuple(velX+fX, velY+fY);
		}
	}
}; 








//AAMIRI

struct CalCurvatures: public thrust::unary_function<CurvatureData, CVec6> {

	uint _maxNodePerCell;
	bool* _isActiveAddr;
	double* _locXAddr;
	double* _locYAddr;

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalCurvatures(uint maxNodePerCell, bool* isActiveAddr,
			double* locXAddr, double* locYAddr) :
			_maxNodePerCell(maxNodePerCell), _isActiveAddr(isActiveAddr), _locXAddr(
					locXAddr), _locYAddr(locYAddr) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec6 operator()(const CurvatureData &bData) const {
		uint activeMembrCount = thrust::get<0>(bData);
		uint cellRank = thrust::get<1>(bData);
		uint nodeRank = thrust::get<2>(bData);
		double f_MI_M_X = thrust::get<3>(bData);
		double f_MI_M_Y = thrust::get<4>(bData);
		double f_MI_M_T= thrust::get<5>(bData);
		double f_MI_M_N = thrust::get<6>(bData);
		double curvature = thrust::get<7>(bData);
		double extForceX = thrust::get<8>(bData);
		double extForceY = thrust::get<9>(bData);
		//double extForceT = thrust::get<10>(bData);
		//double extForceN = thrust::get<11>(bData);

		curvature = 0.0;
		 f_MI_M_T= 0.0;
		 f_MI_M_N= 0.0;
		double extForceT = 0.0;
		double extForceN = 0.0;
                double DistToRi=0.0 ; 

		uint index = cellRank * _maxNodePerCell + nodeRank;
		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount) {
			return thrust::make_tuple(f_MI_M_T,f_MI_M_N, curvature, extForceT, extForceN,DistToRi);
		}

		int index_left = nodeRank - 1;
		if (index_left == -1) {
			index_left = activeMembrCount - 1;
		}
		index_left = index_left + cellRank * _maxNodePerCell;

		int index_right = nodeRank + 1;
		if (index_right == (int) activeMembrCount) {
			index_right = 0;
		}
		index_right = index_right + cellRank * _maxNodePerCell;

		double locX_left = _locXAddr[index_left];
		double locY_left = _locYAddr[index_left];

		double locX_this = _locXAddr[index];
		double locY_this = _locYAddr[index];

		double locX_right = _locXAddr[index_right];
		double locY_right = _locYAddr[index_right];

	double sdelta = 0.000000000001;
//finding the tangent vector
		double Tx_lt = locX_this - locX_left;
		double Ty_lt = locY_this - locY_left;
		double S_lt = sqrt( Tx_lt * Tx_lt + Ty_lt * Ty_lt );
		if (S_lt < sdelta){
		 	Tx_lt = 0.0;
			Ty_lt = 0.0;}
		else {
 			Tx_lt = Tx_lt / S_lt;
			Ty_lt = Ty_lt / S_lt;}

		double Tx_tr = locX_right - locX_this;
		double Ty_tr = locY_right - locY_this;
		double S_tr = sqrt( Tx_tr * Tx_tr + Ty_tr * Ty_tr );
		if (S_tr < sdelta){
			Tx_tr = 0.0;
			Ty_tr = 0.0;}
		else {	
 			Tx_tr = Tx_tr / S_tr;
			Ty_tr = Ty_tr / S_tr;}

		double avgT_x = (Tx_lt + Tx_tr) / 2.0;
		double avgT_y = (Ty_lt + Ty_tr) / 2.0;
		double avgSize = sqrt( avgT_x*avgT_x + avgT_y*avgT_y );
		if (avgSize < sdelta){
			avgT_x = 0.0;
			avgT_y = 0.0;}
		else {
			avgT_x = avgT_x / avgSize;
			avgT_y = avgT_y / avgSize;}

//finding the Normal Vector
		double Nx = Tx_tr - Tx_lt;
		double Ny = Ty_tr - Ty_lt;
		double sizeN = sqrt( Nx*Nx + Ny*Ny );
		if (sizeN < sdelta){
			Nx = 0.0;
			Ny = 0.0;}
		else {
			Nx = Nx / sizeN;
			Ny = Ny / sizeN;}

//calculating the Tangent and Normal Tensions
		f_MI_M_T = f_MI_M_X * avgT_x + f_MI_M_Y * avgT_y;
		f_MI_M_N = f_MI_M_X * Nx     + f_MI_M_Y * Ny;

//finding the curvature at this node
		curvature = sizeN;

//calculating the Tangent and Normal Ext Forces
		extForceT = extForceX * avgT_x + extForceY * avgT_y;
		extForceN = extForceX * Nx     + extForceY * Ny;

                DistToRi=S_tr ; 
		return thrust::make_tuple(f_MI_M_T, abs(f_MI_M_N), curvature, extForceT, abs(extForceN),DistToRi);
	}
};





//Ali
struct AddMembrBend: public thrust::unary_function<BendData, CVec2> {
	uint _maxNodePerCell;
	bool* _isActiveAddr;
	double* _bendLeftXAddr;
	double* _bendLeftYAddr;
	double* _bendRightXAddr;
	double* _bendRightYAddr;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddMembrBend(uint maxNodePerCell, bool* isActiveAddr,
			double* bendLeftXAddr, double* bendLeftYAddr,
			double* bendRightXAddr, double* bendRightYAddr) :
			_maxNodePerCell(maxNodePerCell), _isActiveAddr(isActiveAddr), _bendLeftXAddr(
					bendLeftXAddr), _bendLeftYAddr(bendLeftYAddr), _bendRightXAddr(
					bendRightXAddr), _bendRightYAddr(bendRightYAddr) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec2 operator()(const BendData &bData) const {
		uint activeMembrCount = thrust::get<0>(bData);
		uint cellRank = thrust::get<1>(bData);
		uint nodeRank = thrust::get<2>(bData);
		double oriVelX = thrust::get<3>(bData);
		double oriVelY = thrust::get<4>(bData);

		uint index = cellRank * _maxNodePerCell + nodeRank;
		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount) {
			return thrust::make_tuple(oriVelX, oriVelY);
		}

		int index_left = nodeRank - 1;
		if (index_left == -1) {
			index_left = activeMembrCount - 1;
		}
		index_left = index_left + cellRank * _maxNodePerCell;
		// apply bend force from left
		if (_isActiveAddr[index_left]) {
			oriVelX = oriVelX + _bendRightXAddr[index_left];
			oriVelY = oriVelY + _bendRightYAddr[index_left];
		}

		int index_right = nodeRank + 1;
		if (index_right == (int) activeMembrCount) {
			index_right = 0;
		}
		index_right = index_right + cellRank * _maxNodePerCell;
		// apply bend force from right
		if (_isActiveAddr[index_right]) {
			oriVelX = oriVelX + _bendLeftXAddr[index_right];
			oriVelY = oriVelY + _bendLeftYAddr[index_right];
		}
		return thrust::make_tuple(oriVelX, oriVelY);
	}
};

//Ali modidfied for cell pressure calculation
struct AddSceCellForce: public thrust::unary_function<CellData, CVec6> {
	uint _maxNodePerCell;
	uint _maxMemNodePerCell;
	double* _locXAddr;
	double* _locYAddr;
	bool* _isActiveAddr;
	double _grthPrgrCriVal_M;
	bool* _isEnteringMitotic;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddSceCellForce(uint maxNodePerCell,
			uint maxMemNodePerCell, double* locXAddr, double* locYAddr,
			bool* isActiveAddr, double grthPrgrCriVal_M, bool* isEnteringMitotic) :
			_maxNodePerCell(maxNodePerCell), _maxMemNodePerCell(
					maxMemNodePerCell), _locXAddr(locXAddr), _locYAddr(
					locYAddr), _isActiveAddr(isActiveAddr), _grthPrgrCriVal_M(
					grthPrgrCriVal_M), _isEnteringMitotic(isEnteringMitotic) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec6 operator()(const CellData &cData) const {
		uint activeMembrCount = thrust::get<0>(cData);
		uint activeIntnlCount = thrust::get<1>(cData);
		uint cellRank = thrust::get<2>(cData);
		uint nodeRank = thrust::get<3>(cData);
		double progress = thrust::get<4>(cData);
		double oriVelX = thrust::get<5>(cData);
		double oriVelY = thrust::get<6>(cData);
		uint index = cellRank * _maxNodePerCell + nodeRank;
                
		double F_MI_M_x=0 ; //AliA
		double F_MI_M_y=0 ; //AliA
		double IIEnergyT=0.0 ; 
		double IMEnergyT=0.0 ; 

		if (_isActiveAddr[index] == false) {
			return thrust::make_tuple(oriVelX, oriVelY,F_MI_M_x,F_MI_M_y,IIEnergyT,IMEnergyT); //AliE
		}
		uint intnlIndxMemBegin = cellRank * _maxNodePerCell;
		uint intnlIndxBegin = cellRank * _maxNodePerCell + _maxMemNodePerCell;
		uint intnlIndxEnd = intnlIndxBegin + activeIntnlCount;
		uint index_other;
		double nodeX = _locXAddr[index];
		double nodeY = _locYAddr[index];
		double nodeXOther, nodeYOther;
		// means membrane node
		//Because we want to compute the force on the membrane nodes we modify this function 
		if (nodeRank < _maxMemNodePerCell) {
			bool enteringMitotic = _isEnteringMitotic[cellRank];
			for (index_other = intnlIndxBegin; index_other < intnlIndxEnd;
					index_other++) {
				nodeXOther = _locXAddr[index_other];
				nodeYOther = _locYAddr[index_other]; 
                                /* Ali comment
				calAndAddIB_M(nodeX, nodeY, nodeXOther, nodeYOther, progress,
						oriVelX, oriVelY, _grthPrgrCriVal_M);
                                 */ 
				calAndAddIB_M2(nodeX, nodeY, nodeXOther, nodeYOther, progress,
						oriVelX, oriVelY,F_MI_M_x,F_MI_M_y, _grthPrgrCriVal_M, enteringMitotic);
				CalAndAddIMEnergy(nodeX, nodeY, nodeXOther, nodeYOther, progress,
						IMEnergyT, _grthPrgrCriVal_M);


			}
		} else {
			// means internal node
			bool enteringMitotic = _isEnteringMitotic[cellRank];
			for (index_other = intnlIndxMemBegin;
					index_other < intnlIndxMemBegin + activeMembrCount;
					index_other++) {
				nodeXOther = _locXAddr[index_other];
				nodeYOther = _locYAddr[index_other];
				calAndAddIB_M(nodeX, nodeY, nodeXOther, nodeYOther, progress,
						oriVelX, oriVelY, _grthPrgrCriVal_M, enteringMitotic);
				CalAndAddIMEnergy(nodeX, nodeY, nodeXOther, nodeYOther, progress,
						IMEnergyT, _grthPrgrCriVal_M);


			}
			for (index_other = intnlIndxBegin; index_other < intnlIndxEnd;
					index_other++) {
				if (index_other == index) {
					continue;
				}
				nodeXOther = _locXAddr[index_other];
				nodeYOther = _locYAddr[index_other];
				calAndAddII_M(nodeX, nodeY, nodeXOther, nodeYOther, progress,
						oriVelX, oriVelY, _grthPrgrCriVal_M);
				CalAndAddIIEnergy(nodeX, nodeY, nodeXOther, nodeYOther, progress,
						IIEnergyT, _grthPrgrCriVal_M);
			}
		}
		return thrust::make_tuple(oriVelX, oriVelY,F_MI_M_x,F_MI_M_y,IIEnergyT,IMEnergyT);
	}
};

// struct AddMemContractForce: public thrust::unary_function<DUiDDUiUiBDDT , CVec6> {
// 	uint _maxNodePerCell;
// 	uint _maxMemNodePerCell;
// 	double* _locXAddr;
// 	double* _locYAddr;
// 	MembraneType1* _MemTypeAddr;
// 	int*_MirrorIndexAddr ;
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__host__ __device__ AddMemContractForce(uint maxNodePerCell,
// 			uint maxMemNodePerCell, double* locXAddr, double* locYAddr, MembraneType1* MemTypeAddr, int* MirrorIndexAddr) :
// 			_maxNodePerCell(maxNodePerCell), _maxMemNodePerCell(
// 					maxMemNodePerCell), _locXAddr(locXAddr), _locYAddr(locYAddr),_MemTypeAddr(MemTypeAddr), _MirrorIndexAddr(MirrorIndexAddr) {
// 	}
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__device__ CVec6 operator()(const DUiDDUiUiBDDT & dUiDDUiUiBDDT ) const {
// 		double nucDistToApical  = thrust::get<0>(dUiDDUiUiBDDT );
// 		uint   activeMembrCount = thrust::get<1>(dUiDDUiUiBDDT );
// 		double apicalX		    = thrust::get<2>(dUiDDUiUiBDDT);
// 		double apicalY   		= thrust::get<3>(dUiDDUiUiBDDT );
// 		uint   cellRank  		= thrust::get<4>(dUiDDUiUiBDDT );
// 		uint   nodeRank  		= thrust::get<5>(dUiDDUiUiBDDT );
// 		bool   isActive  		= thrust::get<6>(dUiDDUiUiBDDT );
// 		double oriVelX   		= thrust::get<7>(dUiDDUiUiBDDT );
// 		double oriVelY   		= thrust::get<8>(dUiDDUiUiBDDT );
// 		MembraneType1 nodeType  = thrust::get<9>(dUiDDUiUiBDDT );
		
		
// 		double F_MM_C_X=0 ; //AliA
// 		double F_MM_C_Y=0 ; //AliA
// 		double contractEnergyT=0.0 ; 
		
// 		double locX,locY,locXOther, locYOther;
// 		uint   index ; 
// 		int    index_Other ; 
// 		MembraneType1 nodeTypeOther ;
// 		int basalContractPairId=-1 ; 

		
// 		if ( isActive == false || nodeRank >= _maxMemNodePerCell  ) {
// 			return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
// 		}
// 				// means membrane node

// 		index       = cellRank * _maxNodePerCell + nodeRank;
// 		//if  (  (nodeType==lateralA) || (nodeType==lateralB) ) {
// 		if  ( _MirrorIndexAddr[index] !=-1  ) { 
// 			// This implies that this node is a lateral node of a symmetric pouch cell and because _MirrorIndexAddr is pairwise variable, then automatically action and
// 			// reaction force condition is satisfied.
// 			locX 		= _locXAddr[index];
// 			locY 		= _locYAddr[index];
// 			double nodeDistToApical=sqrt( ( locX-apicalX)*(locX-apicalX) + (locY-apicalY)*(locY-apicalY) )-2  ; // 2 is for saftey to make sure is beneath the nucleus  

// 			index_Other =_MirrorIndexAddr[index]; 
// 			locXOther   = _locXAddr[index_Other];
// 			locYOther   = _locYAddr[index_Other];
// 			double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ; 

// 			if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
//             	calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 				basalContractPairId=index_Other ; 
// 			}

// 			//finished calculating adhesion force
// 			// start calculating Morse force. 
// 			//It assumes that if mirror index of a lateral node of cell is not equal to -1, then the mirror index of all the other lateral nodes of the same cell is not equal to -1. By this restriction the action-reaction force constrain will be automatically satisfied.
// 			uint memIndxBegin = cellRank * _maxNodePerCell;
// 			uint memIndxEnd   = cellRank * _maxNodePerCell +activeMembrCount-1 ;
// 			for (index_Other = memIndxBegin; index_Other <= memIndxEnd;index_Other++) {
// 				locXOther = _locXAddr[index_Other];
// 				locYOther = _locYAddr[index_Other];
// 				double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ;  
		
			 
// 				nodeTypeOther= _MemTypeAddr[index_Other] ; 
// 				if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
	
// 					if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 					}

// 				}
// 			}
// 			return thrust::make_tuple(oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,contractEnergyT,basalContractPairId);
// 		} 
// 		else {
// 		    return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
// 		}
// 	}
// };
// struct AddMemContractForce: public thrust::unary_function<DUiDDUiUiBDDT , CVec6> {
// 	uint _maxNodePerCell;
// 	uint _maxMemNodePerCell;
// 	double* _locXAddr;
// 	double* _locYAddr;
// 	double* _ActomyosinMultipBasal;
// 	double* _ActomyosinMultipApical;
// 	MembraneType1* _MemTypeAddr;
// 	int*_MirrorIndexAddr ;
// 	double _timeRatio;
// 	double _timeRatio_Crit_actomyo;
// 	double _timeRatio_Crit_Division;
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__host__ __device__ AddMemContractForce(uint maxNodePerCell,
// 			uint maxMemNodePerCell, double* locXAddr, double* locYAddr, double* ActomyosinMultipBasal, double* ActomyosinMultipApical, MembraneType1* MemTypeAddr, int* MirrorIndexAddr, 
// 										double timeRatio, double timeRatio_Crit_actomyo, double timeRatio_Crit_Division) :
// 			_maxNodePerCell(maxNodePerCell), _maxMemNodePerCell(
// 					maxMemNodePerCell), _locXAddr(locXAddr), _locYAddr(locYAddr),_ActomyosinMultipBasal(ActomyosinMultipBasal), _ActomyosinMultipApical(ActomyosinMultipApical),_MemTypeAddr(MemTypeAddr), _MirrorIndexAddr(MirrorIndexAddr), 
// 										_timeRatio(timeRatio), _timeRatio_Crit_actomyo(timeRatio_Crit_actomyo), _timeRatio_Crit_Division(timeRatio_Crit_Division) {
// 	}
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__device__ CVec6 operator()(const DUiDDUiUiBDDT & dUiDDUiUiBDDT ) const {
// 		double nucDistToApical  = thrust::get<0>(dUiDDUiUiBDDT );
// 		uint   activeMembrCount = thrust::get<1>(dUiDDUiUiBDDT );
// 		double apicalX		    = thrust::get<2>(dUiDDUiUiBDDT);
// 		double apicalY   		= thrust::get<3>(dUiDDUiUiBDDT );
// 		uint   cellRank  		= thrust::get<4>(dUiDDUiUiBDDT );
// 		uint   nodeRank  		= thrust::get<5>(dUiDDUiUiBDDT );
// 		bool   isActive  		= thrust::get<6>(dUiDDUiUiBDDT );
// 		double oriVelX   		= thrust::get<7>(dUiDDUiUiBDDT );
// 		double oriVelY   		= thrust::get<8>(dUiDDUiUiBDDT );
// 		MembraneType1 nodeType  = thrust::get<9>(dUiDDUiUiBDDT );
		
		
// 		double F_MM_C_X=0 ; //AliA
// 		double F_MM_C_Y=0 ; //AliA
// 		double contractEnergyT=0.0 ; 
		
// 		double locX,locY,locXOther, locYOther, kContrMemb_multip_basal, kContrMemb_multip_apical, kContrMemb_multip2_basal, kContrMemb_multip2_apical;
// 		uint   index ; 
// 		int    index_Other ; 
// 		MembraneType1 nodeTypeOther ;
// 		int basalContractPairId=-1 ; 

// 		double DistFromNucleus;
// 		double percentage_before_timeRatio_Crit_Division_scaling = 2.0;
// 		//This number determines the maximum multiple applied to the basal contractility strength.
// 		//For instance, if it equals to 1.0, it means that we want a maximum of doubling the basal contractility strength.
// 		//And if it equals 2.0, it means that we want a maximum of tripling the basal contractility strength.
// 		//See "kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(1 + 2*percentage_past_timeRatio_Crit);" line for the concept.
// 		double percentage_before_timeRatio_Crit_Division = (_timeRatio)/(_timeRatio_Crit_Division);
		
// 		if (1<0){
// 		// if (cellRank == 31 && _timeRatio <= _timeRatio_Crit_Division){
// 			DistFromNucleus = -2.0 + (7.0 - (-2.0))*(2.0)*percentage_before_timeRatio_Crit_Division; 
// 			//For now we will assuume that new contractile springs are being constructed twice as fast.
// 			if (DistFromNucleus >= 7.0){
// 				DistFromNucleus = 7.0;
// 			}
// 		}
// 		else{
// 			DistFromNucleus = -2.0;
// 		}

// 		if ( isActive == false || nodeRank >= _maxMemNodePerCell  ) {
// 			return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
// 		}
// 				// means membrane node

// 		index       = cellRank * _maxNodePerCell + nodeRank;
// 		//if  (  (nodeType==lateralA) || (nodeType==lateralB) ) {
// 		if  ( _MirrorIndexAddr[index] !=-1  ) { 
// 			// This implies that this node is a lateral node of a symmetric pouch cell and because _MirrorIndexAddr is pairwise variable, then automatically action and
// 			// reaction force condition is satisfied.
// 			locX 		= _locXAddr[index];
// 			locY 		= _locYAddr[index];
// 			// locZ		= _locZAddr[index];
// 			if (_timeRatio < _timeRatio_Crit_actomyo){
// 				kContrMemb_multip_basal = 1.0;
// 				// kContrMemb_multip_apical = 0.0;
// 				if (cellRank==31 && _timeRatio < _timeRatio_Crit_Division){
				
// 					double spectrum = (_ActomyosinMultipBasal[index]*(percentage_before_timeRatio_Crit_Division_scaling + 1) - _ActomyosinMultipBasal[index]);
// 					kContrMemb_multip_basal = _ActomyosinMultipBasal[index] + spectrum*2*percentage_before_timeRatio_Crit_Division;
// 					// kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(1 + 2*percentage_past_timeRatio_Crit);
// 					if (kContrMemb_multip_basal >= _ActomyosinMultipBasal[index]*(percentage_before_timeRatio_Crit_Division_scaling + 1)){
// 						kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(percentage_before_timeRatio_Crit_Division_scaling + 1);
// 					}
				
// 				// The rate of increased contractility is also doubled for now.
// 				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
// 				}
// 			}
// 			else{
// 				kContrMemb_multip_basal = _ActomyosinMultipBasal[index];
// 				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
// 				if (cellRank==31 && _timeRatio < _timeRatio_Crit_Division){
				
// 					double spectrum = (_ActomyosinMultipBasal[index]*(percentage_before_timeRatio_Crit_Division_scaling + 1) - _ActomyosinMultipBasal[index]);
// 					kContrMemb_multip_basal = _ActomyosinMultipBasal[index] + spectrum*2*percentage_before_timeRatio_Crit_Division;
// 					// kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(1 + 2*percentage_past_timeRatio_Crit);
// 					if (kContrMemb_multip_basal >= _ActomyosinMultipBasal[index]*(percentage_before_timeRatio_Crit_Division_scaling + 1)){
// 						kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(percentage_before_timeRatio_Crit_Division_scaling + 1);
// 					}
				
// 				// The rate of increased contractility is also doubled for now.
// 				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
// 				}
// 			}
// 			// double nodeDistToApical=sqrt( ( locX-apicalX)*(locX-apicalX) + (locY-apicalY)*(locY-apicalY) )-2  ; // 2 is for saftey to make sure is beneath the nucleus  
// 			double nodeDistToApical=sqrt( ( locX-apicalX)*(locX-apicalX) + (locY-apicalY)*(locY-apicalY) ); //12/01/2020, edited by Kevin. We will remove the -2 and relocate it too where we are comparing with the nucDistToApical.
// 			index_Other =_MirrorIndexAddr[index]; 
// 			locXOther   = _locXAddr[index_Other];
// 			locYOther   = _locYAddr[index_Other];
// 			// locZOther	= _locZAddr[index_Other];
// 			if (_timeRatio < _timeRatio_Crit_actomyo){
// 				kContrMemb_multip2_basal = 1.0;
// 				// kContrMemb_multip2_apical = 0.0;
// 				if (cellRank==31 && _timeRatio < _timeRatio_Crit_Division){
				
// 					double spectrum = (_ActomyosinMultipBasal[index_Other]*(percentage_before_timeRatio_Crit_Division_scaling + 1) - _ActomyosinMultipBasal[index_Other]);
// 					kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other] + spectrum*1*percentage_before_timeRatio_Crit_Division;
// 					// kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other]*(1 + 2*percentage_past_timeRatio_Crit);
// 					if (kContrMemb_multip2_basal >= _ActomyosinMultipBasal[index_Other]*(percentage_before_timeRatio_Crit_Division_scaling + 1)){
// 						kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other]*(percentage_before_timeRatio_Crit_Division_scaling + 1);
// 					}
				
// 				// The rate of increased contractility is also doubled for now.
// 				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
// 				}
// 			}
// 			else{
// 				kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other];
// 				// kContrMemb_multip2_apical = _ActomyosinMultipApical[index_Other];
// 				if (cellRank==31 && _timeRatio < _timeRatio_Crit_Division){
				
// 					double spectrum = (_ActomyosinMultipBasal[index_Other]*(percentage_before_timeRatio_Crit_Division_scaling + 1) - _ActomyosinMultipBasal[index_Other]);
// 					kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other] + spectrum*1*percentage_before_timeRatio_Crit_Division;
// 					// kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other]*(1 + 2*percentage_past_timeRatio_Crit);
// 					if (kContrMemb_multip2_basal >= _ActomyosinMultipBasal[index_Other]*(percentage_before_timeRatio_Crit_Division_scaling + 1)){
// 						kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other]*(percentage_before_timeRatio_Crit_Division_scaling + 1);
// 					}
				
// 				// The rate of increased contractility is also doubled for now.
// 				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
// 				}
// 			}
// 			// double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ; 
// 			double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) ); //12/01/2020, edited by Kevin.

// 			// if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
// 			// if ( ((nodeDistToApical-2)>nucDistToApical)&& ((nodeDistToApicalOther-2)>nucDistToApical) ) { 
//             // 	calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_basal, kContrMemb_multip2_basal);
// 			// 	basalContractPairId=index_Other ; 
// 			// }
// 			if ( ((nodeDistToApical+DistFromNucleus)>nucDistToApical)&& ((nodeDistToApicalOther+DistFromNucleus)>nucDistToApical) ) { 
				
// 					calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_basal, kContrMemb_multip2_basal);
// 					basalContractPairId=index_Other ;
				
// 			}
// 			// // if ( (nodeDistToApical<nucDistToApical)&& (nodeDistToApicalOther<nucDistToApical) ) { 
// 			// else if ( ((nodeDistToApical+2)<nucDistToApical)&& ((nodeDistToApicalOther+2)<nucDistToApical) ) { 
//             // 	calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_apical, kContrMemb_multip2_apical);
// 			// 	basalContractPairId=index_Other ; 
// 			// }

// 			//finished calculating adhesion force
// 			// start calculating Morse force. 
// 			//It assumes that if mirror index of a lateral node of cell is not equal to -1, then the mirror index of all the other lateral nodes of the same cell is not equal to -1. By this restriction the action-reaction force constrain will be automatically satisfied.
// 			uint memIndxBegin = cellRank * _maxNodePerCell;
// 			uint memIndxEnd   = cellRank * _maxNodePerCell +activeMembrCount-1 ;
// 			for (index_Other = memIndxBegin; index_Other <= memIndxEnd;index_Other++) {
// 				locXOther = _locXAddr[index_Other];
// 				locYOther = _locYAddr[index_Other];
// 				// double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ;  
// 				double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) ); //12/01/2020, edited by Kevin.  
		
			 
// 				nodeTypeOther= _MemTypeAddr[index_Other] ; 
// 				// if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
// 				// if ( ((nodeDistToApical-2)>nucDistToApical)&& ((nodeDistToApicalOther-2)>nucDistToApical) ) { 
// 				// 	if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 // 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 				// 	}

// 				// }
// 				if ( ((nodeDistToApical + DistFromNucleus) > nucDistToApical)&& 
// 					((nodeDistToApicalOther + DistFromNucleus) > nucDistToApical) ) { 
// 					if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 					}

// 				}
// 				// // if ( (nodeDistToApical<nucDistToApical)&& (nodeDistToApicalOther<nucDistToApical) ) { 
// 				// else if ( ((nodeDistToApical+2)<nucDistToApical)&& ((nodeDistToApicalOther+2)<nucDistToApical) ) { 
	
// 				// 	if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 // 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 				// 	}

// 				// }
// 			}
// 			return thrust::make_tuple(oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,contractEnergyT,basalContractPairId);
// 		} 
// 		else {
// 		    return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
// 		}
// 	}
// };

// struct AddMemContractForce_tmp: public thrust::unary_function<DUiDDUiUiBDDT , CVec6> {
// 	uint _maxNodePerCell;
// 	uint _maxMemNodePerCell;
// 	double* _locXAddr;
// 	double* _locYAddr;
// 	MembraneType1* _MemTypeAddr;
// 	int*_MirrorIndexAddr ;
// 	double _timeRatio;
// 	double* _contractActomyo_multip;
// 	double* _contractActomyo_multip_apical;
// 	double _distFromNucleus_max;
// 	double _distFromNucleus_min;
// 	double* _distFromNucleus_normal;
// 	double* _distFromNucleus_normal_apical;
// 	double _percentage_before_timeRatio_Crit_Division_scaling;
// 	bool* _isEnteringMitotic;
// 	double* _contractileSpringGrowthProgress;
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__host__ __device__ AddMemContractForce_tmp(uint maxNodePerCell, uint maxMemNodePerCell, double* locXAddr, double* locYAddr, MembraneType1* MemTypeAddr, int* MirrorIndexAddr, 
// 										double timeRatio,  double* contractActomyo_multip, double* contractActomyo_multip_apical, double distFromNucleus_max, double distFromNucleus_min, double* distFromNucleus_normal, double* distFromNucleus_normal_apical,
// 										double percentage_before_timeRatio_Crit_Division_scaling, bool* isEnteringMitotic, double* contractileSpringGrowthProgress) :
// 			_maxNodePerCell(maxNodePerCell), _maxMemNodePerCell(
// 					maxMemNodePerCell), _locXAddr(locXAddr), _locYAddr(locYAddr),_MemTypeAddr(MemTypeAddr), _MirrorIndexAddr(MirrorIndexAddr), 
// 										_timeRatio(timeRatio), _contractActomyo_multip(contractActomyo_multip),_contractActomyo_multip_apical(contractActomyo_multip_apical),
// 										_distFromNucleus_max(distFromNucleus_max), _distFromNucleus_min(distFromNucleus_min), _distFromNucleus_normal(distFromNucleus_normal), _distFromNucleus_normal_apical(distFromNucleus_normal_apical),
// 										_percentage_before_timeRatio_Crit_Division_scaling(percentage_before_timeRatio_Crit_Division_scaling),
// 										_isEnteringMitotic(isEnteringMitotic),
// 										_contractileSpringGrowthProgress(contractileSpringGrowthProgress) {
// 	}
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__device__ CVec6 operator()(const DUiDDUiUiBDDT & dUiDDUiUiBDDT ) const {
// 		double nucDistToApical  = thrust::get<0>(dUiDDUiUiBDDT );
// 		uint   activeMembrCount = thrust::get<1>(dUiDDUiUiBDDT );
// 		double apicalX		    = thrust::get<2>(dUiDDUiUiBDDT);
// 		double apicalY   		= thrust::get<3>(dUiDDUiUiBDDT );
// 		uint   cellRank  		= thrust::get<4>(dUiDDUiUiBDDT );
// 		uint   nodeRank  		= thrust::get<5>(dUiDDUiUiBDDT );
// 		bool   isActive  		= thrust::get<6>(dUiDDUiUiBDDT );
// 		double oriVelX   		= thrust::get<7>(dUiDDUiUiBDDT );
// 		double oriVelY   		= thrust::get<8>(dUiDDUiUiBDDT );
// 		MembraneType1 nodeType  = thrust::get<9>(dUiDDUiUiBDDT );
		
		
// 		double F_MM_C_X=0 ; //AliA
// 		double F_MM_C_Y=0 ; //AliA
// 		double contractEnergyT=0.0 ; 
		
// 		double locX,locY,locXOther, locYOther, kContrMemb_multip_basal, kContrMemb_multip_apical, kContrMemb_multip2_basal, kContrMemb_multip2_apical;
// 		uint   index ; 
// 		int    index_Other ; 
// 		MembraneType1 nodeTypeOther ;
// 		int basalContractPairId=-1 ; 

// 		double DistFromNucleus, DistFromNucleus_apical;
// 		// double DistFromNucleus_max = 7.0;
// 		// double DistFromNucleus_min = -7.0;
// 		// double percentage_before_timeRatio_Crit_Division_scaling = 4.0;
// 		//This number determines the maximum multiple applied to the basal contractility strength.
// 		//For instance, if it equals to 1.0, it means that we want a maximum of no change in the basal contractility strength.
// 		//And if it equals 2.0, it means that we want a maximum of doubling the basal contractility strength.
// 		//See "kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(1 + 2*percentage_past_timeRatio_Crit);" line for the concept.
// 		// double percentage_before_timeRatio_Crit_Division = (_timeRatio)/(_timeRatio_Crit_Division);
		
// 		// if (1<0){
// 		// if (cellRank == _cellRank_division && _timeRatio <= _timeRatio_Crit_Division){
// 		if (_isEnteringMitotic[cellRank] == true){
// 			DistFromNucleus = _distFromNucleus_min + _contractileSpringGrowthProgress[cellRank];
// 			DistFromNucleus_apical = 99999.9;
// 			if (DistFromNucleus >= _distFromNucleus_max){
// 				DistFromNucleus = _distFromNucleus_max;
// 			}
// 		}
// 		else{
// 			DistFromNucleus = _distFromNucleus_normal[cellRank];
// 			// DistFromNucleus_apical = -1.0*_distFromNucleus_normal[cellRank];
// 			DistFromNucleus_apical = _distFromNucleus_normal_apical[cellRank];
// 		}
// 		// if (_timeRatio == 0 && nodeRank == 0 && cellRank == 0){
// 		// 	std::cout<<"Cell division requires the contractile spring to increase strength by "<<percentage_before_timeRatio_Crit_Division_scaling<<" fold."<<std::endl;
// 		// 	std::cout<<"Contractile spring minimum at "<<DistFromNucleus_min<<" and maximum at "<<DistFromNucleus_max<<" away from the cell center."<<std::endl;
// 		// }

// 		if ( isActive == false || nodeRank >= _maxMemNodePerCell  ) {
// 			return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
// 		}
// 				// means membrane node

// 		index       = cellRank * _maxNodePerCell + nodeRank;
// 		//if  (  (nodeType==lateralA) || (nodeType==lateralB) ) {
// 		if  ( _MirrorIndexAddr[index] !=-1  ) { 
// 			// This implies that this node is a lateral node of a symmetric pouch cell and because _MirrorIndexAddr is pairwise variable, then automatically action and
// 			// reaction force condition is satisfied.
// 			locX 		= _locXAddr[index];
// 			locY 		= _locYAddr[index];
// 			// locZ		= _locZAddr[index];
// 			// if (_timeRatio < _timeRatio_Crit_actomyo){
// 				kContrMemb_multip_basal = _contractActomyo_multip[index];
// 				kContrMemb_multip_apical = _contractActomyo_multip_apical[index];
// 				// kContrMemb_multip_apical = 0.0;
// 				// if (cellRank==_cellRank_division && _timeRatio < _timeRatio_Crit_Division){
// 				if (_isEnteringMitotic[cellRank] == true){
// 					// double spectrum = (1*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]) - 1);
// 					kContrMemb_multip_basal = _contractActomyo_multip[index]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
// 					// kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(1 + 2*percentage_past_timeRatio_Crit);
// 					kContrMemb_multip_apical = 0.0;
// 					if (kContrMemb_multip_basal >= _contractActomyo_multip[index]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index])){
// 						kContrMemb_multip_basal = _contractActomyo_multip[index]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
// 					}
				
// 				// The rate of increased contractility is also doubled for now.
// 				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
// 				}
// 			// }
			
// 			// double nodeDistToApical=sqrt( ( locX-apicalX)*(locX-apicalX) + (locY-apicalY)*(locY-apicalY) )-2  ; // 2 is for saftey to make sure is beneath the nucleus  
// 			double nodeDistToApical=sqrt( ( locX-apicalX)*(locX-apicalX) + (locY-apicalY)*(locY-apicalY) ); //12/01/2020, edited by Kevin. We will remove the -2 and relocate it too where we are comparing with the nucDistToApical.
			
// 			index_Other =_MirrorIndexAddr[index]; 
// 			locXOther   = _locXAddr[index_Other];
// 			locYOther   = _locYAddr[index_Other];
// 			// locZOther	= _locZAddr[index_Other];
// 			// if (_timeRatio < _timeRatio_Crit_actomyo){
// 				kContrMemb_multip2_basal = _contractActomyo_multip[index_Other];
// 				kContrMemb_multip2_apical = _contractActomyo_multip_apical[index_Other];
// 				// kContrMemb_multip2_apical = 0.0;
// 				// if (cellRank==_cellRank_division && _timeRatio < _timeRatio_Crit_Division){
// 				if (_isEnteringMitotic[cellRank] == true){
// 					// double spectrum = (1*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]) - 1);
// 					kContrMemb_multip2_basal = _contractActomyo_multip[index_Other]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
// 					// kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other]*(1 + 2*percentage_past_timeRatio_Crit);
// 					if (kContrMemb_multip2_basal >= _contractActomyo_multip[index_Other]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index])){
// 						kContrMemb_multip2_basal = _contractActomyo_multip[index_Other]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
// 					}
				
// 				// The rate of increased contractility is also doubled for now.
// 				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
// 				}
// 			// }
// 			// double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ; 
// 			double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) ); //12/01/2020, edited by Kevin.

// 			// if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
// 			// if ( ((nodeDistToApical-2)>nucDistToApical)&& ((nodeDistToApicalOther-2)>nucDistToApical) ) { 
//             // 	calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_basal, kContrMemb_multip2_basal);
// 			// 	basalContractPairId=index_Other ; 
// 			// }
// 			if ( ((nodeDistToApical+DistFromNucleus)>nucDistToApical)&& ((nodeDistToApicalOther+DistFromNucleus)>nucDistToApical) ) { 
				
// 					calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_basal, kContrMemb_multip2_basal);
// 					basalContractPairId=index_Other ;
				
// 			}
// 			if ( ((nodeDistToApical+DistFromNucleus_apical)<nucDistToApical)&& ((nodeDistToApicalOther+DistFromNucleus_apical)<nucDistToApical) ) { 
				
// 					calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_apical, kContrMemb_multip2_apical);
// 					basalContractPairId=index_Other ;
				
// 			}
// 			// // if ( (nodeDistToApical<nucDistToApical)&& (nodeDistToApicalOther<nucDistToApical) ) { 
// 			// else if ( ((nodeDistToApical+2)<nucDistToApical)&& ((nodeDistToApicalOther+2)<nucDistToApical) ) { 
//             // 	calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_apical, kContrMemb_multip2_apical);
// 			// 	basalContractPairId=index_Other ; 
// 			// }

// 			//finished calculating adhesion force
// 			// start calculating Morse force. 
// 			//It assumes that if mirror index of a lateral node of cell is not equal to -1, then the mirror index of all the other lateral nodes of the same cell is not equal to -1. By this restriction the action-reaction force constrain will be automatically satisfied.
// 			uint memIndxBegin = cellRank * _maxNodePerCell;
// 			uint memIndxEnd   = cellRank * _maxNodePerCell +activeMembrCount-1 ;
// 			for (index_Other = memIndxBegin; index_Other <= memIndxEnd;index_Other++) {
// 				locXOther = _locXAddr[index_Other];
// 				locYOther = _locYAddr[index_Other];
// 				// double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ;  
// 				double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) ); //12/01/2020, edited by Kevin.  
		
			 
// 				nodeTypeOther= _MemTypeAddr[index_Other] ; 
// 				// if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
// 				// if ( ((nodeDistToApical-2)>nucDistToApical)&& ((nodeDistToApicalOther-2)>nucDistToApical) ) { 
// 				// 	if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 // 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 				// 	}

// 				// }
// 				if ( ((nodeDistToApical + DistFromNucleus) > nucDistToApical)&& 
// 					((nodeDistToApicalOther + DistFromNucleus) > nucDistToApical) ) { 
// 					if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 					}

// 				}
// 				if ( ((nodeDistToApical + DistFromNucleus_apical) < nucDistToApical)&& 
// 					((nodeDistToApicalOther + DistFromNucleus_apical) < nucDistToApical) ) { 
// 					if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 					}

// 				}
// 				// // if ( (nodeDistToApical<nucDistToApical)&& (nodeDistToApicalOther<nucDistToApical) ) { 
// 				// else if ( ((nodeDistToApical+2)<nucDistToApical)&& ((nodeDistToApicalOther+2)<nucDistToApical) ) { 
	
// 				// 	if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
//                 // 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
// 				// 	}

// 				// }
// 			}
// 			return thrust::make_tuple(oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,contractEnergyT,basalContractPairId);
// 		} 
// 		else {
// 		    return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
// 		}
// 	}
// };

struct AddMemContractForce_tmp2: public thrust::unary_function<DUiDDUiUiBDDT , CVec6> {
	uint _maxNodePerCell;
	uint _maxMemNodePerCell;
	double* _locXAddr;
	double* _locYAddr;
	MembraneType1* _MemTypeAddr;
	int*_MirrorIndexAddr ;
	double _timeRatio;
	double* _contractActomyo_multip;
	double* _contractActomyo_multip_apical;
	double _distFromNucleus_max;
	double _distFromNucleus_min;
	double* _distFromNucleus_normal;
	double* _distFromNucleus_normal_apical;
	// double _percentage_before_timeRatio_Crit_Division_scaling;
	double _mitoRndActomyoStrengthScaling;
	bool* _isEnteringMitotic;
	double* _contractileSpringGrowthProgress;
	double* _individualCellHeight;
	double* _distFromBasalLoc;
	double* _distFromApicalLoc;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddMemContractForce_tmp2(uint maxNodePerCell, uint maxMemNodePerCell, double* locXAddr, double* locYAddr, MembraneType1* MemTypeAddr, int* MirrorIndexAddr, 
										double timeRatio,  double* contractActomyo_multip, double* contractActomyo_multip_apical, double distFromNucleus_max, double distFromNucleus_min, double* distFromNucleus_normal, double* distFromNucleus_normal_apical,
										/*double percentage_before_timeRatio_Crit_Division_scaling,*/double mitoRndActomyoStrengthScaling, bool* isEnteringMitotic, double* contractileSpringGrowthProgress, double* individualCellHeight,
										double* distFromBasalLoc, double* distFromApicalLoc) :
			_maxNodePerCell(maxNodePerCell), _maxMemNodePerCell(
					maxMemNodePerCell), _locXAddr(locXAddr), _locYAddr(locYAddr),_MemTypeAddr(MemTypeAddr), _MirrorIndexAddr(MirrorIndexAddr), 
										_timeRatio(timeRatio), _contractActomyo_multip(contractActomyo_multip),_contractActomyo_multip_apical(contractActomyo_multip_apical),
										_distFromNucleus_max(distFromNucleus_max), _distFromNucleus_min(distFromNucleus_min), _distFromNucleus_normal(distFromNucleus_normal), _distFromNucleus_normal_apical(distFromNucleus_normal_apical),
										// _percentage_before_timeRatio_Crit_Division_scaling(percentage_before_timeRatio_Crit_Division_scaling),
										_mitoRndActomyoStrengthScaling(mitoRndActomyoStrengthScaling),
										_isEnteringMitotic(isEnteringMitotic),
										_contractileSpringGrowthProgress(contractileSpringGrowthProgress),
										_individualCellHeight(individualCellHeight),
										_distFromBasalLoc(distFromBasalLoc),
										_distFromApicalLoc(distFromApicalLoc) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec6 operator()(const DUiDDUiUiBDDT & dUiDDUiUiBDDT ) const {
		double nucDistToApical  = thrust::get<0>(dUiDDUiUiBDDT );
		uint   activeMembrCount = thrust::get<1>(dUiDDUiUiBDDT );
		double apicalX		    = thrust::get<2>(dUiDDUiUiBDDT);
		double apicalY   		= thrust::get<3>(dUiDDUiUiBDDT );
		uint   cellRank  		= thrust::get<4>(dUiDDUiUiBDDT );
		uint   nodeRank  		= thrust::get<5>(dUiDDUiUiBDDT );
		bool   isActive  		= thrust::get<6>(dUiDDUiUiBDDT );
		double oriVelX   		= thrust::get<7>(dUiDDUiUiBDDT );
		double oriVelY   		= thrust::get<8>(dUiDDUiUiBDDT );
		MembraneType1 nodeType  = thrust::get<9>(dUiDDUiUiBDDT );
		
		
		double F_MM_C_X=0 ; //AliA
		double F_MM_C_Y=0 ; //AliA
		double contractEnergyT=0.0 ; 
		
		double locX,locY,locXOther, locYOther, kContrMemb_multip_basal, kContrMemb_multip_apical, kContrMemb_multip2_basal, kContrMemb_multip2_apical;
		uint   index ; 
		int    index_Other ; 
		MembraneType1 nodeTypeOther ;
		int basalContractPairId=-1 ; 

		double DistFromNucleus, DistFromNucleus_apical;
		double distMaxBasalContrSpringToApical, distMinApicalContrSpringToApical;
		double distMaxBasalContrSpringToApical_shortest_mitotic = _distFromNucleus_min*_individualCellHeight[cellRank];
		double distMaxBasalContrSpringToApical_shortest = _distFromNucleus_normal[cellRank]*_individualCellHeight[cellRank];
		double distMinApicalContrSpringToApical_longest = _distFromNucleus_normal_apical[cellRank]*_individualCellHeight[cellRank];
		// double DistFromNucleus_max = 7.0;
		// double DistFromNucleus_min = -7.0;
		// double percentage_before_timeRatio_Crit_Division_scaling = 4.0;
		//This number determines the maximum multiple applied to the basal contractility strength.
		//For instance, if it equals to 1.0, it means that we want a maximum of no change in the basal contractility strength.
		//And if it equals 2.0, it means that we want a maximum of doubling the basal contractility strength.
		//See "kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(1 + 2*percentage_past_timeRatio_Crit);" line for the concept.
		// double percentage_before_timeRatio_Crit_Division = (_timeRatio)/(_timeRatio_Crit_Division);
		
		// if (1<0){
		// if (cellRank == _cellRank_division && _timeRatio <= _timeRatio_Crit_Division){
		if (_isEnteringMitotic[cellRank] == true){
			// DistFromNucleus = _distFromNucleus_min + _contractileSpringGrowthProgress[cellRank];
			// DistFromNucleus_apical = 99999.9;
			// if (DistFromNucleus >= _distFromNucleus_max){
			// 	DistFromNucleus = _distFromNucleus_max;
			// }
			// distMaxBasalContrSpringToApical = _individualCellHeight[cellRank] - _contractileSpringGrowthProgress[cellRank];
			// distMaxBasalContrSpringToApical = _individualCellHeight[cellRank] - (distMaxBasalContrSpringToApical_shortest+_contractileSpringGrowthProgress[cellRank]);
			// distMinApicalContrSpringToApical = 0.0;
			// if (distMaxBasalContrSpringToApical <= distMaxBasalContrSpringToApical_shortest_mitotic){
			// 	distMaxBasalContrSpringToApical = distMaxBasalContrSpringToApical_shortest_mitotic;
			// }
			//////////////////////////////////////////////////////////
			// //For no "zipping" mitotic rounding case //////////////
			//////////////////////////////////////////////////////////
			distMaxBasalContrSpringToApical = _individualCellHeight[cellRank] - (distMaxBasalContrSpringToApical_shortest+_contractileSpringGrowthProgress[cellRank]);
			distMinApicalContrSpringToApical = 0.0;
			if (distMaxBasalContrSpringToApical <= distMaxBasalContrSpringToApical_shortest_mitotic){
				distMaxBasalContrSpringToApical = distMaxBasalContrSpringToApical_shortest_mitotic;
			}
			
			//////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////
		}
		else{
			// distMaxBasalContrSpringToApical = _individualCellHeight[cellRank] - _distFromBasalLoc[cellRank];
			// if (distMaxBasalContrSpringToApical <= (_individualCellHeight[cellRank] - distMaxBasalContrSpringToApical_shortest)){
				distMaxBasalContrSpringToApical = _individualCellHeight[cellRank] - distMaxBasalContrSpringToApical_shortest;
			// }
			// distMinApicalContrSpringToApical = _distFromApicalLoc[cellRank];
			// if (distMinApicalContrSpringToApical >= distMinApicalContrSpringToApical_longest){
				distMinApicalContrSpringToApical = distMinApicalContrSpringToApical_longest;
			// }

			/*// DistFromNucleus = _distFromNucleus_normal[cellRank];
			// DistFromNucleus_apical = _distFromNucleus_normal_apical[cellRank];
			// if (cellRank >= 28 & cellRank <=34){
			// 	distMinApicalContrSpringToApical = -9999.9;
			// 	distMaxBasalContrSpringToApical = 9999.9;
			// }*/
		}
		// if (_timeRatio == 0 && nodeRank == 0 && cellRank == 0){
		// 	std::cout<<"Cell division requires the contractile spring to increase strength by "<<percentage_before_timeRatio_Crit_Division_scaling<<" fold."<<std::endl;
		// 	std::cout<<"Contractile spring minimum at "<<DistFromNucleus_min<<" and maximum at "<<DistFromNucleus_max<<" away from the cell center."<<std::endl;
		// }

		if ( isActive == false || nodeRank >= _maxMemNodePerCell  ) {
			return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
		}
				// means membrane node

		index       = cellRank * _maxNodePerCell + nodeRank;
		//if  (  (nodeType==lateralA) || (nodeType==lateralB) ) {
		if  ( _MirrorIndexAddr[index] !=-1  ) { 
			// This implies that this node is a lateral node of a symmetric pouch cell and because _MirrorIndexAddr is pairwise variable, then automatically action and
			// reaction force condition is satisfied.
			locX 		= _locXAddr[index];
			locY 		= _locYAddr[index];
			// locZ		= _locZAddr[index];
			// if (_timeRatio < _timeRatio_Crit_actomyo){
				kContrMemb_multip_basal = _contractActomyo_multip[cellRank];//index];
				kContrMemb_multip_apical = _contractActomyo_multip_apical[cellRank];//index];
				// kContrMemb_multip_apical = 0.0;
				// if (cellRank==_cellRank_division && _timeRatio < _timeRatio_Crit_Division){
				if (_isEnteringMitotic[cellRank] == true){
					// double spectrum = (1*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]) - 1);
					kContrMemb_multip_basal = _mitoRndActomyoStrengthScaling;//_contractActomyo_multip[index]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
					// kContrMemb_multip_basal = _ActomyosinMultipBasal[index]*(1 + 2*percentage_past_timeRatio_Crit);
					kContrMemb_multip_apical = 0.0;
					// if (kContrMemb_multip_basal >= _contractActomyo_multip[index]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index])){
					// 	kContrMemb_multip_basal = _contractActomyo_multip[index]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
					// }
				
				// The rate of increased contractility is also doubled for now.
				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
				}
			// }
			
			// double nodeDistToApical=sqrt( ( locX-apicalX)*(locX-apicalX) + (locY-apicalY)*(locY-apicalY) )-2  ; // 2 is for saftey to make sure is beneath the nucleus  
			double nodeDistToApical=sqrt( ( locX-apicalX)*(locX-apicalX) + (locY-apicalY)*(locY-apicalY) ); //12/01/2020, edited by Kevin. We will remove the -2 and relocate it too where we are comparing with the nucDistToApical.
			
			index_Other =_MirrorIndexAddr[index]; 
			locXOther   = _locXAddr[index_Other];
			locYOther   = _locYAddr[index_Other];
			// locZOther	= _locZAddr[index_Other];
			// if (_timeRatio < _timeRatio_Crit_actomyo){
				kContrMemb_multip2_basal = _contractActomyo_multip[cellRank];//index_Other];
				kContrMemb_multip2_apical = _contractActomyo_multip_apical[cellRank];//index_Other];
				// kContrMemb_multip2_apical = 0.0;
				// if (cellRank==_cellRank_division && _timeRatio < _timeRatio_Crit_Division){
				if (_isEnteringMitotic[cellRank] == true){
					// double spectrum = (1*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]) - 1);
					kContrMemb_multip2_basal = _mitoRndActomyoStrengthScaling;//_contractActomyo_multip[index_Other]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
					kContrMemb_multip2_apical = 0.0;
					// kContrMemb_multip2_basal = _ActomyosinMultipBasal[index_Other]*(1 + 2*percentage_past_timeRatio_Crit);
					// if (kContrMemb_multip2_basal >= _contractActomyo_multip[index_Other]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index])){
					// 	kContrMemb_multip2_basal = _contractActomyo_multip[index_Other]*(_percentage_before_timeRatio_Crit_Division_scaling/_contractActomyo_multip[index]);
					// }
				
				// The rate of increased contractility is also doubled for now.
				// kContrMemb_multip_apical = _ActomyosinMultipApical[index];
				}
			// }
			// double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ; 
			double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) ); //12/01/2020, edited by Kevin.

			// if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
			// if ( ((nodeDistToApical-2)>nucDistToApical)&& ((nodeDistToApicalOther-2)>nucDistToApical) ) { 
            // 	calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_basal, kContrMemb_multip2_basal);
			// 	basalContractPairId=index_Other ; 
			// }
			if ( ((nodeDistToApical) > distMaxBasalContrSpringToApical)&& ((nodeDistToApicalOther) > distMaxBasalContrSpringToApical) ) { 
				
					calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_basal, kContrMemb_multip2_basal);
					basalContractPairId=index_Other ;
				
			}
			if ( ((nodeDistToApical) < distMinApicalContrSpringToApical)&& ((nodeDistToApicalOther) < distMinApicalContrSpringToApical) ) { 
				
					calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_apical, kContrMemb_multip2_apical);
					basalContractPairId=index_Other ;
				
			}
			// // if ( (nodeDistToApical<nucDistToApical)&& (nodeDistToApicalOther<nucDistToApical) ) { 
			// else if ( ((nodeDistToApical+2)<nucDistToApical)&& ((nodeDistToApicalOther+2)<nucDistToApical) ) { 
            // 	calAndAddMM_ContractAdh(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,kContrMemb_multip_apical, kContrMemb_multip2_apical);
			// 	basalContractPairId=index_Other ; 
			// }

			//finished calculating adhesion force
			// start calculating Morse force. 
			//It assumes that if mirror index of a lateral node of cell is not equal to -1, then the mirror index of all the other lateral nodes of the same cell is not equal to -1. By this restriction the action-reaction force constrain will be automatically satisfied.
			uint memIndxBegin = cellRank * _maxNodePerCell;
			uint memIndxEnd   = cellRank * _maxNodePerCell +activeMembrCount-1 ;
			for (index_Other = memIndxBegin; index_Other <= memIndxEnd;index_Other++) {
				locXOther = _locXAddr[index_Other];
				locYOther = _locYAddr[index_Other];
				// double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) )-2 ;  
				double nodeDistToApicalOther=sqrt( (locXOther-apicalX)*(locXOther-apicalX) + (locYOther-apicalY)*(locYOther-apicalY) ); //12/01/2020, edited by Kevin.  
		
			 
				nodeTypeOther= _MemTypeAddr[index_Other] ; 
				// if ( (nodeDistToApical>nucDistToApical)&& (nodeDistToApicalOther>nucDistToApical) ) { 
				// if ( ((nodeDistToApical-2)>nucDistToApical)&& ((nodeDistToApicalOther-2)>nucDistToApical) ) { 
				// 	if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
                // 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
				// 	}

				// }
				// if ( ((nodeDistToApical) > distMaxBasalContrSpringToApical)&& 
				// 	((nodeDistToApicalOther) > distMaxBasalContrSpringToApical) ) { 
				// 	if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
                // 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
				// 	}

				// }
				// if ( ((nodeDistToApical) < distMinApicalContrSpringToApical)&& 
				// 	((nodeDistToApicalOther) < distMinApicalContrSpringToApical) ) {
				if  (((nodeDistToApical) < 9999.9) && ((nodeDistToApicalOther) < 9999.9) ) { 
					if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
                		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
					}

				}
				// // if ( (nodeDistToApical<nucDistToApical)&& (nodeDistToApicalOther<nucDistToApical) ) { 
				// else if ( ((nodeDistToApical+2)<nucDistToApical)&& ((nodeDistToApicalOther+2)<nucDistToApical) ) { 
	
				// 	if (  (nodeTypeOther==lateralB && nodeType==lateralA) || (nodeTypeOther==lateralA && nodeType==lateralB) )  {
                // 		calAndAddMM_ContractRepl(locX, locY, locXOther, locYOther,oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y);
				// 	}

				// }
			}
			return thrust::make_tuple(oriVelX, oriVelY,F_MM_C_X,F_MM_C_Y,contractEnergyT,basalContractPairId);
		} 
		else {
		    return thrust::make_tuple(oriVelX, oriVelY,0.0,0.0,0.0,basalContractPairId); //AliE
		}
	}
};


// This structure is currently not being used. It was used when the nucleus was modeled as a point and force interaction between nucleus and other elements were considered.
struct AddNucleusForce: public thrust::unary_function<DDDBDDDD, CVec2> {
	double _grthPrgrCriVal_M;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddNucleusForce(double grthPrgrCriVal_M) :
			 _grthPrgrCriVal_M(grthPrgrCriVal_M) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ CVec2 operator()(const DDDBDDDD &dDDBDDDD) const {
		double nucleusX = thrust::get<0>(dDDBDDDD);
		double nucleusY = thrust::get<1>(dDDBDDDD);
		double progress = thrust::get<2>(dDDBDDDD);
		bool   isActive = thrust::get<3>(dDDBDDDD);
		double nodeX     = thrust::get<4>(dDDBDDDD);
		double nodeY     = thrust::get<5>(dDDBDDDD);
		double oriVelX  = thrust::get<6>(dDDBDDDD);
		double oriVelY  = thrust::get<7>(dDDBDDDD);
                

		if (isActive == false) {
			return thrust::make_tuple(oriVelX, oriVelY); 
		}
		else {
			calAndAddNucleusEffect(nodeX, nodeY, nucleusX, nucleusY, progress,oriVelX, oriVelY,_grthPrgrCriVal_M);
			return thrust::make_tuple(oriVelX, oriVelY);
		}
	}
};






/**
 * Obtain growth speed and direction given node position.
 * @param _gridDimensionX number of grid points in x direction
 * @param _gridDimensionY number of grid points in y direction
 * @param _gridSpacing spacing of the chemical signal mesh.
 * @param _gridMagValue begin address of growth speed vector
 * @param _gridDirXCompValue begin address of growth direction x component vector
 * @param _gridDirYCompValue begin address of growth direction y component vector
 *
 * @param input1 x coordinate of node position
 * @param input2 y coordinate of node position
 *
 * @return output1 growth speed \n
 *         output2 x component of growth direction \n
 *         output3 y component of growth direction \n
 *
 */
struct LoadGridDataToNode: public thrust::unary_function<CVec2, CVec3> {
	uint _gridDimensionX;
	uint _gridDimensionY;
	double _gridSpacing;
	double* _gridMagValue;
	double* _gridDirXCompValue;
	double* _gridDirYCompValue;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ LoadGridDataToNode(uint gridDimensionX,
			uint gridDimensionY, double gridSpacing, double* gridMagValue,
			double* gridDirXCompValue, double* gridDirYCompValue) :
			_gridDimensionX(gridDimensionX), _gridDimensionY(gridDimensionY), _gridSpacing(
					gridSpacing), _gridMagValue(gridMagValue), _gridDirXCompValue(
					gridDirXCompValue), _gridDirYCompValue(gridDirYCompValue) {
	}
	__host__ __device__ CVec3 operator()(const CVec2 &d2) const {
		double xCoord = thrust::get<0>(d2);
		double yCoord = thrust::get<1>(d2);
		uint gridLoc = (uint) (xCoord / _gridSpacing)
				+ (uint) (yCoord / _gridSpacing) * _gridDimensionX;
		double magRes = _gridMagValue[gridLoc];
		double xDirRes = _gridDirXCompValue[gridLoc];
		double yDirRes = _gridDirYCompValue[gridLoc];
		return thrust::make_tuple(magRes, xDirRes, yDirRes);
	}
};

/**
 * Obtain growth speed and direction given node position and chemical field.
 * @param _gridDimensionX number of grid points in x direction
 * @param _gridDimensionY number of grid points in y direction
 * @param _gridSpacing spacing of the chemical signal mesh.
 * @param _gridMagValue begin address of growth speed vector
 * @param _gridDirXCompValue begin address of growth direction x component vector
 * @param _gridDirYCompValue begin address of growth direction y component vector
 *
 * @param input1 x coordinate of node position
 * @param input2 y coordinate of node position
 * @param input3 type of the cell. Could be boundary, FNM or MX
 *
 * @return output1 growth speed \n
 *         output2 x component of growth direction \n
 *         output3 y component of growth direction \n
 *
 */
struct LoadChemDataToNode: public thrust::unary_function<CVec2Type, CVec3> {
	uint _gridDimensionX;
	uint _gridDimensionY;
	double _gridSpacing;
	double* _gridMagValue;
	double* _gridDirXCompValue;
	double* _gridDirYCompValue;
	uint _gridDimensionX2;
	uint _gridDimensionY2;
	double _gridSpacing2;
	double* _gridMagValue2;
	double* _gridDirXCompValue2;
	double* _gridDirYCompValue2;

	__host__ __device__ LoadChemDataToNode(uint gridDimensionX,
			uint gridDimensionY, double gridSpacing, double* gridMagValue,
			double* gridDirXCompValue, double* gridDirYCompValue,
			uint gridDimensionX2, uint gridDimensionY2, double gridSpacing2,
			double* gridMagValue2, double* gridDirXCompValue2,
			double* gridDirYCompValue2) :
			_gridDimensionX(gridDimensionX), _gridDimensionY(gridDimensionY), _gridSpacing(
					gridSpacing), _gridMagValue(gridMagValue), _gridDirXCompValue(
					gridDirXCompValue), _gridDirYCompValue(gridDirYCompValue), _gridDimensionX2(
					gridDimensionX2), _gridDimensionY2(gridDimensionY2), _gridSpacing2(
					gridSpacing2), _gridMagValue2(gridMagValue2), _gridDirXCompValue2(
					gridDirXCompValue2), _gridDirYCompValue2(gridDirYCompValue2) {
	}
	__host__ __device__
	// place holder for eclipse formatter
	CVec3 operator()(const CVec2Type &d2) const {
		double xCoord = thrust::get<0>(d2);
		double yCoord = thrust::get<1>(d2);
		SceNodeType type = thrust::get<2>(d2);
		uint gridLoc = (uint) (xCoord / _gridSpacing)
				+ (uint) (yCoord / _gridSpacing) * _gridDimensionX;
		if (type == FNM) {
			double magRes = _gridMagValue[gridLoc];
			double xDirRes = _gridDirXCompValue[gridLoc];
			double yDirRes = _gridDirYCompValue[gridLoc];
			return thrust::make_tuple(magRes, xDirRes, yDirRes);
		} else if (type == MX) {
			double magRes = _gridMagValue2[gridLoc];
			double xDirRes = _gridDirXCompValue2[gridLoc];
			double yDirRes = _gridDirYCompValue2[gridLoc];
			return thrust::make_tuple(magRes, xDirRes, yDirRes);
		} else {
			return thrust::make_tuple(0.0, 1.0, 0.0);
		}

	}
};

/**
 * One dimensional version of a*X plus Y.
 * @param input1 X
 * @param input2 Y
 *
 * @return output1 a*X+Y
 */
struct SaxpyFunctor: public thrust::binary_function<double, double, double> {
	double _dt;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ SaxpyFunctor(double dt) :
			_dt(dt) {
	}
	__host__ __device__
	double operator()(const double &x, const double &y) {
		return _dt * x + y;
	}
};

struct MultiWithLimit: public thrust::unary_function<double, double> {
	double _k, _bound;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ MultiWithLimit(double k, double bound) :
			_k(k), _bound(bound) {
	}
	__host__ __device__
	double operator()(const double &x) {
		if (x <= 0) {
			return 0;
		}
		double tmpRes = x * _k;
		if (tmpRes < _bound) {
			return tmpRes;
		} else {
			return _bound;
		}
	}
};
//Ali simplifies: ration between the internal element and membrane nodes is not checked anymore 
struct AdjustMembrGrow: public thrust::unary_function<UiDD, double> {
	/*
	 * Growth speed set to be constant when growth is necessary.
	 */
	double _constSpeed;

	/*
	 * Initial count of membrane elements
	 */
	uint _initMembrCt;

	/*
	 * Initial count of internal elements
	 */
	uint _initIntnlCt;

	__host__ __device__ //place holder for eclipse formatter
	AdjustMembrGrow(double constSpeed, uint initMembrCt, uint initIntnlCt) :
			_constSpeed(constSpeed), // place holder for eclipse formatter
			_initMembrCt(initMembrCt), // place holder for eclipse formatter
			_initIntnlCt(initIntnlCt) {
	}
	__device__
	double operator()(const UiUi &input) const {
		uint curActiveMembrNode = thrust::get<0>(input);
		uint curActiveIntnlNode = thrust::get<1>(input);

		// Force conversion of double to integer
		uint targetMembrCt = sqrt(double(curActiveIntnlNode) / _initIntnlCt)
				* _initMembrCt;

		if (curActiveMembrNode < targetMembrCt) {
			return _constSpeed;
		} else {
			//return 0;
			return _constSpeed;
		}
	}
};




//Ali struct MemGrowFunc: public thrust::unary_function<DUi, BoolD> {
struct MemGrowFunc: public thrust::unary_function<UiDDBoolIITI, BoolDII> {
	uint _bound;
	bool _isInitPhase ; 
	int _maxApicalBasalNodeNum;
	double _maxLengthToAddMemNodes;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ MemGrowFunc(uint bound, bool isInitPhase, int maxApicalBasalNodeNum, double maxLengthToAddMemNodes) :
			_bound(bound), _isInitPhase(isInitPhase), _maxApicalBasalNodeNum(maxApicalBasalNodeNum), _maxLengthToAddMemNodes(maxLengthToAddMemNodes) {
	}
	//Ali __host__ __device__ BoolD operator()(const DUi& dui) {
	__host__ __device__ BoolDII operator()(const UiDDBoolIITI& uiddbooliiti) {
		//Ali double progress = thrust::get<0>(dui);
		uint   curActiveMembrNode = thrust::get<0>(uiddbooliiti); //Ali
		double progress = thrust::get<1>(uiddbooliiti); //Ali
        double LengthMax=thrust::get<2>(uiddbooliiti); //Ali
		bool isEnteringMitotic=thrust::get<3>(uiddbooliiti);
		int numApicalNode = thrust::get<4>(uiddbooliiti);
		int numBasalNode = thrust::get<5>(uiddbooliiti);
		MembraneType1 newNodeType = thrust::get<6>(uiddbooliiti);
		int cellRank = thrust::get<7>(uiddbooliiti);
        // double cellProgress=thrust::get<3>(uiddd); //Ali
		//Ali uint curActiveMembrNode = thrust::get<1>(dui);
		if (isEnteringMitotic==true){
			return thrust::make_tuple(false, 0, numApicalNode, numBasalNode);
		}
		else if (cellRank>1 && cellRank<63 && newNodeType == apical1 && numApicalNode >= _maxApicalBasalNodeNum){
			return thrust::make_tuple(false, 0, numApicalNode, numBasalNode);
		}
		else if (cellRank>1 && cellRank<63 && newNodeType == basal1 && numBasalNode >= _maxApicalBasalNodeNum){
			return thrust::make_tuple(false, 0, numApicalNode, numBasalNode);
		}
		else if (cellRank>85 && newNodeType == apical1 && numApicalNode >= _maxApicalBasalNodeNum){
			return thrust::make_tuple(false, 0, numApicalNode, numBasalNode);
		}
		else if (cellRank>85 && newNodeType == basal1 && numBasalNode >= _maxApicalBasalNodeNum){
			return thrust::make_tuple(false, 0, numApicalNode, numBasalNode);
		}
		else{
			if (curActiveMembrNode < _bound   && LengthMax>_maxLengthToAddMemNodes){//0.195){// && cellProgress>0.1 && _isInitPhase==false) {
			//if (curActiveMembrNode < _bound && LengthMax>0.15 ) {
			//if (curActiveMembrNode < _bound  && LengthMax>0.15 && cellProgress<-0.001)  {   // to add node if in the initial condition negative progress is introduced.
				if (newNodeType == apical1 && numApicalNode < _maxApicalBasalNodeNum){
					return thrust::make_tuple(true, 0, numApicalNode+1, numBasalNode);
				}
				else if (newNodeType == basal1 && numBasalNode < _maxApicalBasalNodeNum){
					return thrust::make_tuple(true, 0, numApicalNode, numBasalNode+1);
				}
				// else if (cellRank == 0 && newNodeType != apical1 && newNodeType != basal1){
				// 	return thrust::make_tuple(true, 0, numApicalNode, numBasalNode);
				// }
				// else if (cellRank == 1 && newNodeType != apical1 && newNodeType != basal1){
				// 	return thrust::make_tuple(true, 0, numApicalNode, numBasalNode);
				// }
				// else if (cellRank == 63 && newNodeType != apical1 && newNodeType != basal1){
				// 	return thrust::make_tuple(true, 0, numApicalNode, numBasalNode);
				// }
				// else if (cellRank == 64 && newNodeType != apical1 && newNodeType != basal1){
				// 	return thrust::make_tuple(true, 0, numApicalNode, numBasalNode);
				// }
				else{
					return thrust::make_tuple(false, 0, numApicalNode, numBasalNode);
				}
			}
			//	else if (curActiveMembrNode < _bound  && LengthMax>0.15 && cellProgress>0.05)  {   // to not add new node for recently divided cells.
			//	return thrust::make_tuple(true, 0);
		//	} 
			else {
				// return thrust::make_tuple(false, progress);
				return thrust::make_tuple(false, 0, numApicalNode, numBasalNode);
			}
		}
	}
};

//Ali
struct MemDelFunc: public thrust::unary_function<UiDDD, BoolD> {
	uint _bound;
	bool _isInitPhase ; 
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ MemDelFunc(uint bound, bool isInitPhase) :
			_bound(bound), _isInitPhase(isInitPhase)  {
	}
	//Ali __host__ __device__ BoolD operator()(const DUi& dui) {
	__host__ __device__ BoolD operator()(const UiDDD& uiddd) {
		//Ali double progress = thrust::get<0>(dui);
		uint   curActiveMembrNode = thrust::get<0>(uiddd); //Ali
		double progress = thrust::get<1>(uiddd); //Ali
        double LengthMin=thrust::get<2>(uiddd); //Ali
        double cellProgress=thrust::get<3>(uiddd); //Ali
		//Ali uint curActiveMembrNode = thrust::get<1>(dui);
		//if (curActiveMembrNode < _bound && progress >= 1.0 && LengthMax>0.0975 ) {
		//if (curActiveMembrNode > 0  && LengthMin<0.06 && cellProgress>0.05 ) {
		if (curActiveMembrNode > 0  && LengthMin<0.1 && cellProgress>0.1 &&  _isInitPhase==true) {
	//		return thrust::make_tuple(false,progress); // by pass for now to not loose apical nodes
			return thrust::make_tuple(false, progress); 
		} 
		
		//if (curActiveMembrNode > 0  && LengthMin<0.06 && cellProgress<-0.001 ) {
		//	return thrust::make_tuple(true,progress);
			//return thrust::make_tuple(false,progress); // bypass for now to not loose apical nodes
	//	}
		else {
			return thrust::make_tuple(false, progress);
		}
	}
};


/**
 * One dimensional version of a*X plus Y, return one if result is larger than one.
 * @param input1 X
 * @param input2 Y
 *
 * @return output1 a*X+Y
 */
struct SaxpyFunctorWithMaxOfOne: public thrust::binary_function<double, double,
		double> {
	double _dt;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	SaxpyFunctorWithMaxOfOne(double dt) :
			_dt(dt) {
	}
	__host__ __device__
	double operator()(const double &x, const double &y) {
		double result = _dt * x + y;
		if (result > 1.0) {
			return 1.0;
		} else {
			return result;
		}
	}
};

/**
 * Two dimensional version of a*X plus Y.
 * @param input1 x and y components of X
 * @param input2 x and y components of Y
 *
 * @return output1 x and y compoents of result
 */
struct SaxpyFunctorDim2: public thrust::binary_function<CVec2, CVec2, CVec2> {
	double _dt;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ SaxpyFunctorDim2(double dt) :
			_dt(dt) {
	}
	__host__ __device__ CVec2 operator()(const CVec2 &vec1, const CVec2 &vec2) {
		double xRes = thrust::get<0>(vec1) * _dt + thrust::get<0>(vec2);
		double yRes = thrust::get<1>(vec1) * _dt + thrust::get<1>(vec2);
		return thrust::make_tuple(xRes, yRes);
	}
};

//Ali
struct SaxpyFunctorDim2_Damp: public thrust::binary_function<CVec2, CVec2, CVec2> {
        double _dt;
        double _DampCoef ; 
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ SaxpyFunctorDim2_Damp(double dt, double Damp_Coef) :
                        _dt(dt), _DampCoef(Damp_Coef) 
                        {
	}
	__host__ __device__ CVec2 operator()(const CVec2 &vec1, const CVec2 &vec2) {
		
		double xRes = thrust::get<0>(vec1) * _dt/_DampCoef + thrust::get<0>(vec2);
		double yRes = thrust::get<1>(vec1) * _dt/_DampCoef + thrust::get<1>(vec2);
		if (yRes>21.5) {
			return thrust::make_tuple(xRes, 21.5);
		}
		else if (yRes<17.11) {

			return thrust::make_tuple(xRes, 17.11);
		}
		else {

			return thrust::make_tuple(xRes, yRes);
		}
	}
};
//Ali 
struct SaxpyFunctorDim2_BC_Damp: public thrust::binary_function<CVec3, CVec2, CVec2> {
        double _dt;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ SaxpyFunctorDim2_BC_Damp(double dt) :
                        _dt(dt) 
                        {
	}
	__host__ __device__ CVec2 operator()(const CVec3 &vec1, const CVec2 &vec2) {
		double xRes = thrust::get<1>(vec1) * _dt/thrust::get<0>(vec1) + thrust::get<0>(vec2);
		double yRes = thrust::get<2>(vec1) * _dt/thrust::get<0>(vec1) + thrust::get<1>(vec2);

		
			return thrust::make_tuple(xRes, yRes);

	}
};


/**


 * Point condition operater, decide if cell is ready to add a new point.
 * @param _threshold threshold value for difference of current progress and last checkpoint.
 * if difference is bigger than threshold then the cell is ready for adding a new node.
 * @param input1 growth progress \n
 * @param input2 last check point \n
 * @return output1 is the cell going to add one more node?
 * @return output2 updated check point value (change or unchanged)
 */
struct PtCondiOp: public thrust::unary_function<CVec2, bool> {
	double _threshold;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ PtCondiOp(double threshold) :
			_threshold(threshold) {
	}
	__host__ __device__
	bool operator()(const CVec2 &d2) const {
		double progress = thrust::get<0>(d2);
		double lastCheckPoint = thrust::get<1>(d2);
		bool resBool = false;
		if (progress == 1.0 && lastCheckPoint < 1.0) {
			resBool = true;
		}
		if (progress - lastCheckPoint >= _threshold) {
			resBool = true;
		}
		return resBool;
	}
};



//AAMIRI May5

struct isDelOp: public thrust::unary_function<UiDDBool, bool> {
	double _laserCenterX;
	double _laserCenterY;
	double _ablationRadius;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ isDelOp(double laserCenterX, double laserCenterY, double ablationRadius) :
			_laserCenterX(laserCenterX), _laserCenterY(laserCenterY), _ablationRadius(ablationRadius) {
	}
	__host__ __device__
	bool operator()(const UiDDBool &d2) const {

		uint cellRank = thrust::get<0>(d2);
		double CellCenterX = thrust::get<1>(d2);
		double CellCenterY = thrust::get<2>(d2);
		bool resBool = thrust::get<3>(d2);

		if (resBool == true){
			return resBool;}

		double distToLaser = sqrt( (_laserCenterX-CellCenterX)*(_laserCenterX-CellCenterX) + (_laserCenterY-CellCenterY)*(_laserCenterY-CellCenterY) );
		if (distToLaser < _ablationRadius){
		    resBool = true;}

		return resBool;
	}
};


/**
 * return zero given a celltype
 */
struct GetZero: public thrust::unary_function<SceNodeType, double> {
	__host__ __device__
	double operator()(const SceNodeType &type) {
		return 0.0;
	}
};
/**
 * determines if cell type is boundary.
 */
struct IsBoundary: public thrust::unary_function<SceNodeType, bool> {
	__host__ __device__ uint operator()(const SceNodeType &type) {
		if (type == Boundary) {
			return true;
		} else {
			return false;
		}
	}
};

/**
 * Unary opterator for adding new node in the cell.
 * BoolUIDDUI consists of the following:
 *
 * (1) - (Bool,bool) is this cell scheduled to grow?
 *
 * (2) - (UI,unsigned integer) how many active nodes are there in this cell?
 * we need this input to decide where should we place the coordinate information of the new node
 *
 * (3) - (D, double) x coordinate of the cell center
 *
 * (4) - (D, double) y coordinate of the cell center
 * we need these two cell center coordinates because cuda only has a pseduo-random number generator,
 * so we need to obtain a good seed to generate a random number. Here we choose center position of the cell.
 *
 * (5) - (UI, unsigned integer) rank of the cell
 *
 * BoolUI consists of the following:
 *
 * (1) - (Bool,bool) if operation succeed, this will return 0. otherwise, return 1
 *
 * (2) - (UI,unsigned integer) how many active nodes are there in this cell? if operation succeed,
 * this will input active node count + 1. otherwise, return input active node count
 *
 * @param _maxNodeOfOneCell Maximum node count of a cell.
 * @param _addNodeDistance  While adding a node, we need to set a fixed distance as radius of the circle
 *        that we would like to add a point.
 * @param _minDistanceToOtherNode Minimum distance of the newly added point to any other node.
 *        If the distance of the newly added node is greater than this min distance,
 *        the add operation will fail and the method will change nothing.
 * @param _nodeIsActiveAddress pointer to the begining of vector nodeIsActive of SceNodes
 * @param _nodeXPosAddress pointer to the begining of vector nodeLocX of SceNodes
 * @param _nodeYPosAddress pointer to the begining of vector nodeLocY of SceNodes
 */

// struct progress_BCImp: thrust::unary_function<DDUi, double> {

// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	
// 	double _dt;
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
// 	__host__ __device__ progress_BCImp(double dt) :
// 			_dt(dt) {
// 	}


// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__device__ double operator()(const DDUi &ddi) {
// 		double growProgressOld = thrust::get<0>(ddi);
// 		// double growSpeed = thrust::get<1>(ddi);
// 		uint    cellRank = thrust::get<2>(ddi);

// 		// double growProgress=growProgressOld+growSpeed*_dt;
// 		double growProgress=growProgressOld+0.001*_dt;
// 		if (cellRank < 2){
// 			growProgress=0;
// 		}
// 		else if (cellRank > 62 && cellRank < 86){
// 			growProgress=0;
// 		}
		
//        //         if (cellRank==5 || cellRank==6) {
// 	//	return (growProgressOld);
// 	//	}
// 		if (growProgress>1.0) {
// 		return (1.0);
//                 }
// 		else {
// 		return (growProgress) ; 
// 		}
// 	}


// };

struct progress_BCImp: thrust::unary_function<DDUi, double> {

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	
	double _growthProgressSpeed;
	int* _daughterCellProduced;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ progress_BCImp(double growthProgressSpeed, int* daughterCellProduced) :
			_growthProgressSpeed(growthProgressSpeed), _daughterCellProduced(daughterCellProduced) {
	}


	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ double operator()(const DDUi &ddi) {
		double growProgressOld = thrust::get<0>(ddi);
		// double growSpeed = thrust::get<1>(ddi);
		uint    cellRank = thrust::get<2>(ddi);

		// double growProgress=growProgressOld+growSpeed*_dt;
		if (_daughterCellProduced[cellRank] < 10){
			double growProgress=growProgressOld+_growthProgressSpeed;
			if (cellRank < 2){
				growProgress=0;
			}
			else if (cellRank > 62 && cellRank < 86){
				growProgress=0;
			}
			
		//         if (cellRank==5 || cellRank==6) {
		//	return (growProgressOld);
		//	}
			if (growProgress>1.0) {
				return (1.0);
			}
			else {
				return (growProgress) ; 
			}
		}
		else{
			return (0.0);
		}
	}


};

struct progress_BCImp_Ver2: thrust::unary_function<DDUi, double> {

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	
	double _growthProgressSpeed;
	int* _daughterCellProduced;
	int* _cellRankFront;
	int* _cellRankBehind;
	double* _currentGrowthProgress;
	double _mitoticThreshold;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight__host__ __device__
	__host__ __device__ progress_BCImp_Ver2(double growthProgressSpeed, int* daughterCellProduced,
										 int* cellRankFront, int* cellRankBehind, double* currentGrowthProgress, double mitoticThreshold) :
			_growthProgressSpeed(growthProgressSpeed), _daughterCellProduced(daughterCellProduced),
							 _cellRankFront(cellRankFront), _cellRankBehind(cellRankBehind), _currentGrowthProgress(currentGrowthProgress), _mitoticThreshold(mitoticThreshold) {
	}


	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ double operator()(const DDUi &ddi) {
		double growProgressOld = thrust::get<0>(ddi);
		// double growSpeed = thrust::get<1>(ddi);
		uint    cellRank = thrust::get<2>(ddi);

		// double growProgress=growProgressOld+growSpeed*_dt;
		if (_daughterCellProduced[cellRank] < 10){
			if (_currentGrowthProgress[_cellRankFront[cellRank]] < _mitoticThreshold && _currentGrowthProgress[_cellRankBehind[cellRank]] < _mitoticThreshold){
				double growProgress=growProgressOld+_growthProgressSpeed;
				if (cellRank < 2){
					growProgress=0;
				}
				else if (cellRank > 62 && cellRank < 86){
					growProgress=0;
				}
				
			//         if (cellRank==5 || cellRank==6) {
			//	return (growProgressOld);
			//	}
				if (growProgress>1.0) {
					return (1.0);
				}
				else {
					return (growProgress) ; 
				}
			}
			else{
				double growProgress=growProgressOld;
				if (cellRank < 2){
					growProgress=0;
				}
				else if (cellRank > 62 && cellRank < 86){
					growProgress=0;
				}
				
			//         if (cellRank==5 || cellRank==6) {
			//	return (growProgressOld);
			//	}
				if (growProgress>1.0) {
					return (1.0);
				}
				else {
					return (growProgress) ; 
				}
			}
		}
		else{
			return (0.0);
		}
	}


};



struct AddPtOp: thrust::unary_function<BoolUIDDUID, BoolUID> {
	uint _maxNodeOfOneCell;
	double _addNodeDistance;
	double _minDistanceToOtherNode;
	bool* _nodeIsActiveAddress;
	double* _nodeXPosAddress;
	double* _nodeYPosAddress;
	double _growThreshold;

	unsigned int m_seed;

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddPtOp(uint maxNodeOfOneCell, double addNodeDistance,
			double minDistanceToOtherNode, bool* nodeIsActiveAddress,
			double* nodeXPosAddress, double* nodeYPosAddress, uint seed,
			double growThreshold) :
			_maxNodeOfOneCell(maxNodeOfOneCell), _addNodeDistance(
					addNodeDistance), _minDistanceToOtherNode(
					minDistanceToOtherNode), _nodeIsActiveAddress(
					nodeIsActiveAddress), _nodeXPosAddress(nodeXPosAddress), _nodeYPosAddress(
					nodeYPosAddress), _growThreshold(growThreshold), m_seed(
					seed) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ BoolUID operator()(const BoolUIDDUID &biddi) {
		const double pI = acos(-1.0);
		bool isScheduledToGrow = thrust::get<0>(biddi);
		uint activeNodeCountOfThisCell = thrust::get<1>(biddi);
		double lastCheckPoint = thrust::get<5>(biddi);
		if (isScheduledToGrow == false) {
			return thrust::make_tuple(isScheduledToGrow,
					activeNodeCountOfThisCell, lastCheckPoint);
		}
		double cellCenterXCoord = thrust::get<2>(biddi);
		double cellCenterYCoord = thrust::get<3>(biddi);
		uint cellRank = thrust::get<4>(biddi);

		bool isSuccess = true;

		thrust::default_random_engine rng(m_seed);

		// discard n numbers to avoid correlation
		rng.discard(cellRank);

		thrust::uniform_real_distribution<double> u0Pi(0, 2.0 * pI);
		double randomAngle = u0Pi(rng);
		double xOffset = _addNodeDistance * cos(randomAngle);
		double yOffset = _addNodeDistance * sin(randomAngle);
		double xCoordNewPt = cellCenterXCoord + xOffset;
		double yCoordNewPt = cellCenterYCoord + yOffset;
		uint cellNodeStartPos = cellRank * _maxNodeOfOneCell;
		uint cellNodeEndPos = cellNodeStartPos + activeNodeCountOfThisCell;
		for (uint i = cellNodeStartPos; i < cellNodeEndPos; i++) {
			double distance = sqrt(
					(xCoordNewPt - _nodeXPosAddress[i])
							* (xCoordNewPt - _nodeXPosAddress[i])
							+ (yCoordNewPt - _nodeYPosAddress[i])
									* (yCoordNewPt - _nodeYPosAddress[i]));
			if (distance < _minDistanceToOtherNode) {
				isSuccess = false;
				break;
			}
		}

		if (isSuccess) {
			_nodeXPosAddress[cellNodeEndPos] = xCoordNewPt;
			_nodeYPosAddress[cellNodeEndPos] = yCoordNewPt;
			_nodeIsActiveAddress[cellNodeEndPos] = true;
			isScheduledToGrow = false;
			activeNodeCountOfThisCell = activeNodeCountOfThisCell + 1;
			lastCheckPoint = lastCheckPoint + _growThreshold;
			if (lastCheckPoint > 1.0) {
				lastCheckPoint = 1.0;
			}
		}
		return thrust::make_tuple(isScheduledToGrow, activeNodeCountOfThisCell,
				lastCheckPoint);
	}

};

struct AddPtOp_M: thrust::unary_function<BoolUIDDUID, DUi> {
	uint _seed;
	double _addNodeDistance;
	double _growThreshold;
	double* _nodeXPosAddress;
	double* _nodeYPosAddress;
	bool* _nodeIsActiveAddress;

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddPtOp_M(uint seed, double addNodeDistance,
			double growThreshold, double* nodeXPosAddress,
			double* nodeYPosAddress, bool* nodeIsActiveAddress) :
			_seed(seed), _addNodeDistance(addNodeDistance), _growThreshold(
					growThreshold), _nodeXPosAddress(nodeXPosAddress), _nodeYPosAddress(
					nodeYPosAddress), _nodeIsActiveAddress(nodeIsActiveAddress) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ DUi operator()(const BoolUIDDUID &biddi) {
		bool isScheduledToGrow = thrust::get<0>(biddi);
		uint activeMembrNodeThis = thrust::get<1>(biddi);
		double lastCheckPoint = thrust::get<5>(biddi);

		bool isFull = isAllIntnlFilled(activeMembrNodeThis);
		if (!isScheduledToGrow || isFull) {
			return thrust::make_tuple(lastCheckPoint, activeMembrNodeThis);
		}

		double cellCenterXCoord = thrust::get<2>(biddi);
		double cellCenterYCoord = thrust::get<3>(biddi);
		uint cellRank = thrust::get<4>(biddi);
		double randomAngle = obtainRandAngle(cellRank, _seed);
		double xOffset = _addNodeDistance * cos(randomAngle);
		double yOffset = _addNodeDistance * sin(randomAngle);
		double xCoordNewPt = cellCenterXCoord + xOffset;
		double yCoordNewPt = cellCenterYCoord + yOffset;

		uint cellNodeEndPos = obtainNewIntnlNodeIndex(cellRank,
				activeMembrNodeThis);
		_nodeXPosAddress[cellNodeEndPos] = xCoordNewPt;
		_nodeYPosAddress[cellNodeEndPos] = yCoordNewPt;
		_nodeIsActiveAddress[cellNodeEndPos] = true;
		activeMembrNodeThis = activeMembrNodeThis + 1;
		lastCheckPoint = lastCheckPoint + _growThreshold;
		if (lastCheckPoint > 1.0) {
			lastCheckPoint = 1.0;
		}

		return thrust::make_tuple(lastCheckPoint, activeMembrNodeThis);
	}

};



//AAMIRI
struct DelPtOp_M: thrust::unary_function<BoolUIDDUIUIBoolD, UiUiBD> {
	uint _seed;
	int _timeStep;
	double _growThreshold;
	double* _nodeXPosAddress;
	double* _nodeYPosAddress;
	bool* _nodeIsActiveAddress;
	int* _adhIndxAddr;
	
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ DelPtOp_M(uint seed, int timeStep,
			int* adhIndxAddr, double* nodeXPosAddress,
			double* nodeYPosAddress, bool* nodeIsActiveAddress) :
			_seed(seed), _timeStep(timeStep), _adhIndxAddr(
					adhIndxAddr), _nodeXPosAddress(nodeXPosAddress),
					 _nodeYPosAddress(nodeYPosAddress), _nodeIsActiveAddress(nodeIsActiveAddress) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__device__ UiUiBD operator()(const BoolUIDDUIUIBoolD &biddi) {
		bool isScheduledToShrink = thrust::get<0>(biddi);
		uint activeIntnlNodeThis = thrust::get<1>(biddi);
		uint cellRank = thrust::get<4>(biddi);
		uint activeMembrNodeThis = thrust::get<5>(biddi);

		//bool isFull = isAllIntnlFilled(activeIntnlNodeThis);
		bool isIntnlEmptied = isAllIntnlEmptied(activeIntnlNodeThis);//AAMIRI
		bool isMembrEmptied = isAllMembrEmptied(activeMembrNodeThis);


		bool isCellActive = thrust::get<6>(biddi);
		double growthSpeed = thrust::get<7>(biddi);

		if (!isScheduledToShrink || (isIntnlEmptied && isMembrEmptied) /*|| cellRank != 0*/ ) {
			return thrust::make_tuple(activeMembrNodeThis, activeIntnlNodeThis, isCellActive, growthSpeed);
		}
		
		double cellCenterXCoord = thrust::get<2>(biddi);
		double cellCenterYCoord = thrust::get<3>(biddi);
		int randMembID = obtainRemovingMembrNodeID(cellRank, activeMembrNodeThis, _seed);
		int membEndNode = obtainMembEndNode(cellRank, activeMembrNodeThis);

		uint cellNodeEndPos = obtainLastIntnlNodeIndex(cellRank,
				activeIntnlNodeThis);

		double delta = 0.000001;
		if (/*!isIntnlEmptied*/activeIntnlNodeThis>1 && _timeStep%80==0){
		_nodeXPosAddress[cellNodeEndPos-1] = 0.0 + delta;
		_nodeYPosAddress[cellNodeEndPos-1] = 0.0 + delta;
		_nodeIsActiveAddress[cellNodeEndPos-1] = false;
		_adhIndxAddr[cellNodeEndPos-1] = -1;
	//	_membrIntnlIndex[cellNodeEndPos-1] = -1;
		activeIntnlNodeThis = activeIntnlNodeThis - 1;
		}

		if (/*!isMembrEmptied*/activeMembrNodeThis>2 && _timeStep%50==0){
		    for (int m=randMembID; m<membEndNode; m++){
			_nodeXPosAddress[m] = _nodeXPosAddress[m+1];
			_nodeYPosAddress[m] = _nodeYPosAddress[m+1];
			_adhIndxAddr[m] = _adhIndxAddr[m+1];
			_nodeIsActiveAddress[m] = _nodeIsActiveAddress[m+1];}
		
/*			_nodeXPosAddress[randMembID] = _nodeXPosAddress[membEndNode];
			_nodeYPosAddress[randMembID] = _nodeYPosAddress[membEndNode];
			_adhIndxAddr[randMembID] = _adhIndxAddr[membEndNode];
			_nodeIsActiveAddress[randMembID] = _nodeIsActiveAddress[membEndNode];*/

		_nodeXPosAddress[membEndNode] = 0.0 + delta;
		_nodeYPosAddress[membEndNode] = 0.0 + delta;
		_nodeIsActiveAddress[membEndNode] = false;
		_adhIndxAddr[membEndNode] = -1;
	//	_membrIntnlIndex[membEndNode] = -1;
		activeMembrNodeThis = activeMembrNodeThis - 1;
		}

		if (activeMembrNodeThis == 2){
		_nodeXPosAddress[membEndNode] = 0.0 + delta;
		_nodeYPosAddress[membEndNode] = 0.0 + delta;
		_nodeXPosAddress[membEndNode - 1] = 0.0 + delta;
		_nodeYPosAddress[membEndNode - 1] = 0.0 + delta;

		_adhIndxAddr[membEndNode] = -1;
		_adhIndxAddr[membEndNode - 1] = -1;

		}

		if (activeIntnlNodeThis == 1){
		_nodeXPosAddress[cellNodeEndPos-1] = 0.0 + delta;
		_nodeYPosAddress[cellNodeEndPos-1] = 0.0 + delta;
		_adhIndxAddr[cellNodeEndPos-1] = -1; 	
		}

		if ( (activeIntnlNodeThis+activeMembrNodeThis) == 2 ){
		isCellActive = false;
		growthSpeed = 0.0;
		}


		return thrust::make_tuple(activeMembrNodeThis, activeIntnlNodeThis, isCellActive, growthSpeed);
	}

};

/**
 * Compute the target length of a cell given growth progress.
 * @param _cellInitLength initial length of a cell. (when growth progress = 0)
 * @param _cellFinalLength final length of a cell. (when growth progress =1)
 * @param input1 progress cell growth progress.
 * @return cell expected length
 */
struct CompuTarLen: thrust::unary_function<double, double> {
	double _cellInitLength, _cellFinalLength;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CompuTarLen(double initLen, double finalLen) :
			_cellInitLength(initLen), _cellFinalLength(finalLen) {
	}
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__
	double operator()(const double &progress) {
		return _cellInitLength + progress * (_cellFinalLength - _cellInitLength);
	}
};

/**
 * Compute the distance of a node to its corresponding center, return 0 if node is inactive.
 * @param input1 x component of center position of cell center
 * @param input2 y component of center position of cell center
 * @param input3 x component of cell growth direction
 * @param input4 y component of cell growth direction
 * @param input5 x component of node location
 * @param input6 y component of node location
 * @param input7 flag for node activeness
 */
struct CompuDist: thrust::unary_function<CVec6Bool, double> {
	__host__ __device__
	double operator()(const CVec6Bool &vec6b) {
		double centerXPos = thrust::get<0>(vec6b);
		double centerYPos = thrust::get<1>(vec6b);
		double growthXDir = thrust::get<2>(vec6b);
		double growthYDir = thrust::get<3>(vec6b);
		double nodeXPos = thrust::get<4>(vec6b);
		double nodeYPos = thrust::get<5>(vec6b);
		bool nodeIsActive = thrust::get<6>(vec6b);
		if (!nodeIsActive) {
			// All nodes that are inactive will be omitted.
			// I choose 0 because 0 will not be either maximum or minimum
			return 0;
		} else {
			double dirModule = sqrt(
					growthXDir * growthXDir + growthYDir * growthYDir);
			return ((nodeXPos - centerXPos) * (growthXDir) / dirModule
					+ (nodeYPos - centerYPos) * growthYDir / dirModule);
		}
	}
};

/**
 * Compute difference of cell expected length and current length.
 * @param input1 expected length of the cell
 * @param input2 minimum distance of nodes of the cell to its corresponding center along growth direction
 * @param input3 maximum distance of nodes of the cell to its corresponding center along growth direction
 * @return difference of expected and current length.
 */
struct CompuDiff: thrust::unary_function<CVec3, double> {
	__host__ __device__
	double operator()(const CVec3 &vec3) {
		double expectedLen = thrust::get<0>(vec3);
		// minimum distance of node to its corresponding center along growth direction
		double minDistance = thrust::get<1>(vec3);
		double maxDistance = thrust::get<2>(vec3);
		return (expectedLen - (maxDistance - minDistance));
	}
};

/**
 * Apply stretch force to all cell nodes.
 * @param _elongationCoefficient elongationForce = _elongationCoefficient*distInElongationDirection
 * 			* elongateDirection;
 * @param input1 distToCenterAlongGrowDir distance of a node to the corresponding cell center along growth direction
 * @param input2 lengthDifference length difference of the expected length of a cell and currentl length of the same cell.
 * @param input3 x component of growth direction.
 * @param input4 y component of growth direction.
 * @param input5 x direction of original velocity
 * @param input6 y direction of original velocity
 */
struct ApplyStretchForce: thrust::unary_function<CVec6, CVec2> {
	double _elongationCoefficient;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ ApplyStretchForce(double elongationCoefficient) :
			_elongationCoefficient(elongationCoefficient) {
	}
	__host__ __device__ CVec2 operator()(const CVec6 &vec6) {
		double distToCenterAlongGrowDir = thrust::get<0>(vec6);
		// minimum distance of node to its corresponding center along growth direction
		double lengthDifference = thrust::get<1>(vec6);
		double growthXDir = thrust::get<2>(vec6);
		double growthYDir = thrust::get<3>(vec6);
		double originalVelX = thrust::get<4>(vec6);
		double originalVelY = thrust::get<5>(vec6);
		double xRes = lengthDifference * _elongationCoefficient
				* distToCenterAlongGrowDir * growthXDir;
		xRes = xRes + originalVelX;
		double yRes = lengthDifference * _elongationCoefficient
				* distToCenterAlongGrowDir * growthYDir;
		yRes = yRes + originalVelY;
		return thrust::make_tuple(xRes, yRes);
	}
};

struct ApplyStretchForce_M: thrust::unary_function<CVec6UI, CVec2> {
	double _elongationCoefficient;
	double _typeThreshold;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ ApplyStretchForce_M(double elongationCoefficient,
			uint threshold) :
			_elongationCoefficient(elongationCoefficient), _typeThreshold(
					threshold) {
	}
	__host__ __device__ CVec2 operator()(const CVec6UI &vec6ui) {
		double distToCenterAlongGrowDir = thrust::get<0>(vec6ui);
		// minimum distance of node to its corresponding center along growth direction
		double lengthDifference = thrust::get<1>(vec6ui);
		double growthXDir = thrust::get<2>(vec6ui);
		double growthYDir = thrust::get<3>(vec6ui);
		double originalVelX = thrust::get<4>(vec6ui);
		double originalVelY = thrust::get<5>(vec6ui);
		uint nodeRank = thrust::get<6>(vec6ui);
		if (nodeRank < _typeThreshold) {
			return thrust::make_tuple(originalVelX, originalVelY);
		} else {
			double xRes = lengthDifference * _elongationCoefficient
					* distToCenterAlongGrowDir * growthXDir;
			xRes = xRes + originalVelX;
			double yRes = lengthDifference * _elongationCoefficient
					* distToCenterAlongGrowDir * growthYDir;
			yRes = yRes + originalVelY;
			return thrust::make_tuple(xRes, yRes);
		}

	}
};

struct ApplyChemoVel: thrust::unary_function<CVec5, CVec2> {
	double _chemoCoefficient;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ ApplyChemoVel(double chemoCoefficient) :
			_chemoCoefficient(chemoCoefficient) {
	}
	__host__ __device__ CVec2 operator()(const CVec5 &vec5) {
		double growthSpeed = thrust::get<0>(vec5);
		double growthXDir = thrust::get<1>(vec5);
		double growthYDir = thrust::get<2>(vec5);
		double originalVelX = thrust::get<3>(vec5);
		double originalVelY = thrust::get<4>(vec5);
		double xRes = growthSpeed * _chemoCoefficient * growthXDir;
		xRes = xRes + originalVelX;
		double yRes = growthSpeed * _chemoCoefficient * growthYDir;
		yRes = yRes + originalVelY;
		return thrust::make_tuple(xRes, yRes);
	}
};

/**
 * compute the left shifted global position of a node.
 * @param _shiftLeftOffset number of spaces the node should left shift \n
 * @param input original global position of a node \n
 * @return output shifted global position of a node.\n
 */
struct LeftShiftFunctor: thrust::unary_function<uint, uint> {
	uint _shiftLeftOffset;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ LeftShiftFunctor(uint maxNodeOfOneCell) :
			_shiftLeftOffset(maxNodeOfOneCell / 2) {
	}
	__host__ __device__ uint operator()(const uint &position) {
		uint result;
		if (position < _shiftLeftOffset) {
			// could be 0, because these region will actually never be used
			result = 0;
		} else {
			result = position - _shiftLeftOffset;
		}
		return result;
	}
};

/**
 * decide if a node, given by its global rank, is on the right side of a cell.
 * @param _maxNodeCountPerCell maximum number of nodes per cell \n
 * @param _halfMaxNode half of maximum number of nodes per cell \n
 * @param nodeGlobalRank global rank of a node \n
 * @return IsRightSide : true if is on the left side.\n
 */
struct IsRightSide: thrust::unary_function<uint, bool> {
	uint _maxNodeCountPerCell;
	uint _halfMaxNode;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ IsRightSide(uint maxNodeOfOneCell) :
			_maxNodeCountPerCell(maxNodeOfOneCell), _halfMaxNode(
					maxNodeOfOneCell / 2) {
	}
	__host__ __device__
	bool operator()(const uint &position) {
		if (position % _maxNodeCountPerCell < _halfMaxNode) {
			return false;
		} else {
			return true;
		}
	}
};

/**
 * decide if a node, given by its global rank, is on the left side of a cell.
 * @param _maxNodeCountPerCell maximum number of nodes per cell \n
 * @param _halfMaxNode half of maximum number of nodes per cell \n
 * @param nodeGlobalRank global rank of a node \n
 * @return IsLeftSide : true if is on the left side.\n
 */
struct IsLeftSide: thrust::unary_function<uint, bool> {
	uint _maxNodeCountPerCell;
	uint _halfMaxNode;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ IsLeftSide(uint maxNodeOfOneCell) :
			_maxNodeCountPerCell(maxNodeOfOneCell), _halfMaxNode(
					maxNodeOfOneCell / 2) {
	}
	__host__ __device__
	bool operator()(const uint &position) {
		if (position % _maxNodeCountPerCell < _halfMaxNode) {
			return true;
		} else {
			return false;
		}
	}
};

/**
 * Given rank of a node inside a cell and rank of the cell, get the global rank of the node.
 * @param _maxNodeCountPerCell maximum number of nodes of a cell
 * @param vec first input: rank of a node inside a cell. \n
 * second input: rank of the cell \n
 * @return nodePosition global rank of a node
 */
struct CompuPos: thrust::unary_function<Tuint2, uint> {
	uint _maxNodeCountPerCell;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CompuPos(uint maxNodeOfOneCell) :
			_maxNodeCountPerCell(maxNodeOfOneCell) {
	}
	__host__ __device__ uint operator()(const Tuint2 &vec) {
		uint rankInCell = thrust::get<0>(vec) % _maxNodeCountPerCell;
		uint cellRank = thrust::get<1>(vec);
		return (cellRank * _maxNodeCountPerCell + rankInCell);
	}
};

/**
 * struct for decide if a cell is ready to divide.
 * @param _isDivideCriticalRatio If the length difference to expected length
 *     is less than this critical ratio and growth progress is equal or bigger than 1.0
 *     it means the cell is ready to divide.
 * @param vec first input : length difference of current length and expected length \n
 * second input: expected length \n
 * thrid input: growth progress. should be 0.0 to 1.0. \n
 * @return isGoingToDivide result that indicates whether a cell is ready to divide.
 */
struct CompuIsDivide: thrust::unary_function<CVec3Int, BoolD> {
	double _isDivideCriticalRatio;
	uint _maxNodePerCell;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CompuIsDivide(double isDivideCriticalRatio,
			uint maxNodePerCell) :
			_isDivideCriticalRatio(isDivideCriticalRatio), _maxNodePerCell(
					maxNodePerCell) {
	}
	__host__ __device__ BoolD operator()(const CVec3Int &vec) {
		double lengthDifference = thrust::get<0>(vec);
		double expectedLength = thrust::get<1>(vec);
		double currentLength = expectedLength - lengthDifference;
		double growthProgress = thrust::get<2>(vec);
		uint nodeCount = thrust::get<3>(vec);
		if (currentLength / expectedLength > _isDivideCriticalRatio
				&& growthProgress >= 1.0 && nodeCount == _maxNodePerCell) {
			return thrust::make_tuple(true, 0.0);
		} else {
			return thrust::make_tuple(false, growthProgress);
		}
	}
};

// struct CompuIsDivide_M: thrust::unary_function<DUi, bool> {
// 	uint _maxIntnlNodePerCell;
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__host__ __device__ CompuIsDivide_M(uint maxIntnlNodePerCell) :
// 			_maxIntnlNodePerCell(maxIntnlNodePerCell) {
// 	}
// 	__host__ __device__
// 	bool operator()(const DUi &vec) {
// 		double growthProgress = thrust::get<0>(vec);
// 		uint nodeCount = thrust::get<1>(vec);
// 		if (growthProgress >= 1.0 && nodeCount == _maxIntnlNodePerCell) { // if we are extremly ulucky there is a chance that growth progress is > 1 but nodes are not full 
// 			// and in the growth function there is no mechanism to check and add more nodes.
// 			return true;
// 		} else {
// 			return false;
// 		}
// 	}
// };
struct CompuIsDivide_M: thrust::unary_function<DUi, bool> {
	uint _targetCellDividingArea;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CompuIsDivide_M(double targetCellDividingArea) :
			_targetCellDividingArea(targetCellDividingArea) {
	}
	__host__ __device__
	bool operator()(const DUi &vec) {
		double growthProgress = thrust::get<0>(vec);
		double currentCellArea = thrust::get<1>(vec);
		if (growthProgress >= 1.0){//_targetCellDividingArea) { // if we are extremly ulucky there is a chance that growth progress is > 1 but nodes are not full 
			// and in the growth function there is no mechanism to check and add more nodes.
			return true;
		} else {
			return false;
		}
	}
};

//A&A
// struct CompuIsEnteringMitotic_M: thrust::unary_function<CVec2, bool> {
// 	double _grthprgCriVal ; 
// 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
// 	__host__ __device__ CompuIsEnteringMitotic_M(double grthprgCriVal_M) :
// 			_grthprgCriVal(grthprgCriVal_M) {
// 	}
// 	__host__ __device__
// 	bool operator()(const CVec2 &vec) {
// 		double growthProgress = thrust::get<0>(vec);
// 		double growthProgressOld = thrust::get<1>(vec);
		
// 		if (growthProgress >= _grthprgCriVal &&  growthProgressOld <= _grthprgCriVal) {
// 			return true;
// 		} else {
// 			return false;
// 		}
// 	}
// };
struct CompuIsEnteringMitotic_M: thrust::unary_function<CVec2, bool> {
	double _grthprgCriVal ; 
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CompuIsEnteringMitotic_M(double grthprgCriVal_M) :
			_grthprgCriVal(grthprgCriVal_M) {
	}
	__host__ __device__
	bool operator()(const CVec2 &vec) {
		double growthProgress = thrust::get<0>(vec);
		// double growthProgressOld = thrust::get<1>(vec);
		
		if (growthProgress >= _grthprgCriVal ){//&&  growthProgressOld <= _grthprgCriVal) {
			return true;
		} else {
			return false;
		}
	}
};

//AAMIRI
/*
struct CompuIsRemoving_M: thrust::unary_function<DUi, bool> {
	uint _maxIntnlNodePerCell;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CompuIsDivide_M(uint maxIntnlNodePerCell) :
			_maxIntnlNodePerCell(maxIntnlNodePerCell) {
	}
	__host__ __device__
	bool operator()(const DUi &vec) {
		double growthProgress = thrust::get<0>(vec);
		uint nodeCount = thrust::get<1>(vec);
		if ( nodeCount == _maxIntnlNodePerCell - _maxIntnlNodePerCell) {
			return true;
		} else {
			return false;
		}
	}
};
*/

/**
 * Functor for modify veolcities of all nodes given node type and isActive
 * @param input1: take velocity , type and isActive info of node
 * @return output: modified velocity.
 */
struct VelocityModifier: public thrust::unary_function<Vel2DActiveTypeRank,
		CVec2> {
	uint beginPosOfProfileNodes;
	uint currentActiveProfileNodes;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ VelocityModifier(uint beginPos,
			uint currentProfileNodeCount) {
		beginPosOfProfileNodes = beginPos;
		currentActiveProfileNodes = currentProfileNodeCount;
	}
	__host__ __device__
	// place holder for eclipse formatter
	CVec2 operator()(const Vel2DActiveTypeRank &nodeInfo) {
		double velX = thrust::get<0>(nodeInfo);
		double velY = thrust::get<1>(nodeInfo);
		bool isActive = thrust::get<2>(nodeInfo);
		SceNodeType type = thrust::get<3>(nodeInfo);
		uint nodeRank = thrust::get<4>(nodeInfo);
		// boundary nodes should not move. Also, inactive nodes should not move.
		if (type == Boundary || type == Cart || isActive == false) {
			return thrust::make_tuple(0.0, 0.0);
		}
		// The end nodes of the profile should be fixed.
		if (type == Profile
				&& (nodeRank == beginPosOfProfileNodes
						|| nodeRank
								== (beginPosOfProfileNodes
										+ currentActiveProfileNodes - 1))) {
			return thrust::make_tuple(0.0, 0.0);
		}
		return thrust::make_tuple(velX, velY);
	}
};

struct ForceZero: public thrust::unary_function<CVec2, CVec2> {
	__host__ __device__ CVec2 operator()(const CVec2 &oriData) {
		return thrust::make_tuple(0.0, 0.0);
	}
};

struct AdjustGrowth: public thrust::unary_function<UiDD, BoolDD> {
	uint _halfMax;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AdjustGrowth(uint halfMax) :
			_halfMax(halfMax) {
	}
	__host__ __device__ BoolDD operator()(const UiDD &growData) {
		uint curIntnlNodeCount = thrust::get<0>(growData);
		double curProgress = thrust::get<1>(growData);
		double lastPoint = thrust::get<2>(growData);
		if (curIntnlNodeCount <= _halfMax) {
			curProgress = 0;
			lastPoint = 0;
		}
		return thrust::make_tuple(false, curProgress, lastPoint);
	}
};

struct AssignRandIfNotInit: public thrust::unary_function<CVec3BoolInt,
		CVec3Bool> {
	double _lowerLimit, _upperLimit;
	uint _currentCellCount, _randAux;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AssignRandIfNotInit(double low, double high,
			uint currentCellCount, uint randAux) :
			_lowerLimit(low), _upperLimit(high), _currentCellCount(
					currentCellCount), _randAux(randAux) {
	}
	__host__ __device__ CVec3Bool operator()(const CVec3BoolInt &inputInfo) {
		uint preSeed = _currentCellCount / _randAux;
		double currentDirX = thrust::get<1>(inputInfo);
		double currentDirY = thrust::get<2>(inputInfo);
		bool isInitBefore = thrust::get<3>(inputInfo);
		uint seed = thrust::get<4>(inputInfo) + preSeed;
		thrust::default_random_engine rng;
		thrust::uniform_real_distribution<double> dist(_lowerLimit,
				_upperLimit);

		if (isInitBefore) {
			rng.discard(seed);
			double randomNum = dist(rng);
			return thrust::make_tuple(randomNum, currentDirX, currentDirY, true);
		} else {
			rng.discard(seed);
			double randomNum1 = dist(rng);
			thrust::uniform_real_distribution<double> dist2(0, 2 * PI);
			rng.discard(seed);
			double randomNum2 = dist2(rng);
			double xDir = cos(randomNum2);
			double yDir = sin(randomNum2);
			return thrust::make_tuple(randomNum1, xDir, yDir, true);
		}
	}
};
//Ali modified
struct RandomizeGrow_M: public thrust::unary_function<TypeCVec3BoolInt, CVec3Bool> {
	double _lowerLimit, _upperLimit;
	double _minY,_maxY ; 
	uint _seed;
	//thrust::default_random_engine rng;
	thrust::uniform_real_distribution<double> dist;
//	thrust::uniform_real_distribution<double> dist2;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ RandomizeGrow_M(double minY, double maxY, double low, double high, uint seed) :
			_minY(minY),_maxY(maxY),_lowerLimit(low), _upperLimit(high), _seed(seed) {
	}
	__host__ __device__ CVec3Bool operator()(const TypeCVec3BoolInt &inputInfo) {
		ECellType  cellType= thrust::get<0>(inputInfo);
		double curSpeed = thrust::get<1>(inputInfo);
		double centerCellX = thrust::get<2>(inputInfo);
		double centerCellY = thrust::get<3>(inputInfo);
		bool isInitBefore = thrust::get<4>(inputInfo);
		uint cellRank = thrust::get<5>(inputInfo);
		if (isInitBefore) {
			return thrust::make_tuple(curSpeed, centerCellX, centerCellY, true);
		} else {
			if (cellType==pouch) {
				thrust:: minstd_rand rng ; 
				thrust::uniform_real_distribution<double> dist3(_lowerLimit,_upperLimit);
				uint seedNew = _seed + cellRank;
				rng.discard(seedNew);
				//double distanceY=abs (centerCellY-_minY) ; 
		//		double randomNum1 = 1.89*exp(-2*distanceY/(_maxY-_minY))*dist(rng);
				double randomNum1 =dist3(rng);
			
				//rng.discard(seedNew);
  	//			double randomNum2 = dist2(rng);
				//double xDir = cos(randomNum2);
				//double yDir = sin(randomNum2);
				return thrust::make_tuple(randomNum1, centerCellX,centerCellY, true);
			}
			else {
				return thrust::make_tuple(0.0, centerCellX,centerCellY, true);
			}
		}
	}
};

struct AssignFixedGrowth: public thrust::unary_function<CVec3BoolInt, CVec3> {
	double _speed;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AssignFixedGrowth(double fixedSpeed) :
			_speed(fixedSpeed) {
	}
	__host__ __device__ CVec3 operator()(const CVec3BoolInt &inputInfo) {
		return thrust::make_tuple(_speed, 1, 0);
	}
};

struct AddMemNode: public thrust::unary_function<TuuuddII, uint> {
	uint _maxNodePerCell;
	bool* _isActiveAddr;
	double* _xPosAddr, *_yPosAddr;
	int* _adhIndxAddr;
	MembraneType1* _memNodeType ; 
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ AddMemNode(uint maxNodePerCell, bool* isActiveAddr,
			double* xPosAddr, double* yPosAddr, int* adhIndxAddr, MembraneType1* memNodeType) :
			_maxNodePerCell(maxNodePerCell), _isActiveAddr(isActiveAddr), _xPosAddr(
					xPosAddr), _yPosAddr(yPosAddr), _adhIndxAddr(adhIndxAddr), _memNodeType(memNodeType) {
	}
	__device__ uint operator()(const TuuuddII &oriData) {
		uint cellRank = thrust::get<0>(oriData);
		uint insertIndx = thrust::get<1>(oriData) + 1; // newIndex 
		uint curActCount = thrust::get<2>(oriData);
		double insertX = thrust::get<3>(oriData);
		double insertY = thrust::get<4>(oriData);
		int iDApical=	thrust::get<5>(oriData); 
		int iDBasal=	thrust::get<6>(oriData); 
		uint globalIndxEnd = cellRank * _maxNodePerCell + curActCount; //membrane nodes are first. End position based on newindex
		uint globalIndexInsert = cellRank * _maxNodePerCell + insertIndx;
		// if (insertIndx<=iDApical) {  //since the current acrive membrane nodes is one more, it can not be the last ID.
		// 	iDApical=iDApical+1 ;
		// }

		// if (insertIndx<=iDBasal) {
		// 	iDBasal=iDBasal+1 ;
		// }
		for (uint i = globalIndxEnd; i >= globalIndexInsert; i--) {
			_isActiveAddr[i] = _isActiveAddr[i - 1];
			_xPosAddr[i] = _xPosAddr[i - 1];
			_yPosAddr[i] = _yPosAddr[i - 1];
			//_adhIndxAddr[i] = _adhIndxAddr[i - 1];
			_adhIndxAddr[i] = -1;
			_memNodeType[i]=_memNodeType[i-1] ; //Ali 
		}
		_isActiveAddr[globalIndexInsert] = true;
		_xPosAddr[globalIndexInsert] = insertX;
		_yPosAddr[globalIndexInsert] = insertY;
		_adhIndxAddr[globalIndexInsert] = -1;
		_memNodeType[globalIndexInsert] = _memNodeType[globalIndexInsert-1]; // to have the same type of the membrane node as at least one of its neighbors
		// if (_memNodeType[globalIndexInsert-1] != apical1 || _memNodeType[globalIndexInsert-1] != basal1){
		// 	_memNodeType[globalIndexInsert] = _memNodeType[globalIndexInsert+1];
		// }
		//return (curActCount + 1);
			return curActCount+1;// , iDApical,iDBasal);
	}
};
//Ali
struct DelMemNode: public thrust::unary_function<TuuuII, UiII> {
	uint _maxNodePerCell;
	bool* _isActiveAddr;
	double* _xPosAddr, *_yPosAddr;
	int* _adhIndxAddr;
	MembraneType1* _memNodeType ; 

	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ DelMemNode(uint maxNodePerCell, bool* isActiveAddr,
			double* xPosAddr, double* yPosAddr, int* adhIndxAddr, MembraneType1* memNodeType) :
			_maxNodePerCell(maxNodePerCell), _isActiveAddr(isActiveAddr), _xPosAddr(
					xPosAddr), _yPosAddr(yPosAddr), _adhIndxAddr(adhIndxAddr),_memNodeType(memNodeType) {
	}
	__device__ UiII operator()(const TuuuII &oriData) {
		uint cellRank = thrust::get<0>(oriData);
		uint delIndx = thrust::get<1>(oriData) ; //+1
		uint curActCount = thrust::get<2>(oriData);
		int iDApical=	thrust::get<3>(oriData); 
		int iDBasal=	thrust::get<4>(oriData); 

		uint globalIndxEnd = cellRank * _maxNodePerCell + curActCount-1; // old end
		uint globalIndexDel = cellRank * _maxNodePerCell + delIndx;
		int shiftValue ; 
		// we only shift the candidate node for division, if it is an apical node. 
		//If the apical node is at the end of indexing, the next for loop becomes complicated and we simply delete the node on the other side.
		//shiftValue=1 ; 
		//if (globalIndexDel==globalIndxEnd){ 			
		//	shiftValue=-1 ; 
	//	}
	//	if (_memNodeType[globalIndexDel]==apical1) {
	//		globalIndexDel=globalIndexDel+shiftValue ; 
	//		delIndx=delIndx+shiftValue ; 
	//	}

		if (delIndx<iDApical) {
			iDApical=iDApical-1 ;
		}

		if (delIndx<iDBasal) {
			iDBasal=iDBasal-1 ;
		}

		if (delIndx==iDApical || delIndx==iDBasal) {

			return thrust::make_tuple(curActCount , iDApical,iDBasal);
		}
		else {

			for (uint i =globalIndexDel+1; i<=globalIndxEnd; i++) {
				_isActiveAddr[i-1] = _isActiveAddr[i];
				_xPosAddr[i-1] = _xPosAddr[i];
				_yPosAddr[i-1] = _yPosAddr[i];
				_adhIndxAddr[i-1] = _adhIndxAddr[i];
				_memNodeType[i-1]=_memNodeType[i] ; 
			}
		 	_isActiveAddr[globalIndxEnd]=false ;
		 	_adhIndxAddr[globalIndxEnd] = -1;
		 	_memNodeType[globalIndxEnd]=notAssigned1 ; 

			return thrust::make_tuple(curActCount-1 , iDApical,iDBasal);
		}
	}
};





struct CalTriArea: public thrust::unary_function<Tuuudd, double> {
	uint _maxNodePerCell;
	bool* _isActiveAddr;
	double* _locXAddr;
	double* _locYAddr;
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__ CalTriArea(uint maxNodePerCell, bool* isActiveAddr,
			double* locXAddr, double* locYAddr) :
			_maxNodePerCell(maxNodePerCell), _isActiveAddr(isActiveAddr), _locXAddr(
					locXAddr), _locYAddr(locYAddr) {
	}
	__device__
	double operator()(const Tuuudd &inputData) const {
		uint activeMembrCount = thrust::get<0>(inputData);
		uint cellRank = thrust::get<1>(inputData);
		uint nodeRank = thrust::get<2>(inputData);
		double centerX = thrust::get<3>(inputData);
		double centerY = thrust::get<4>(inputData);
		uint index = cellRank * _maxNodePerCell + nodeRank;

		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount ) {
			return 0.0;
		} else {
			int index_right = nodeRank + 1;
			if (index_right == (int) activeMembrCount) {
				index_right = 0;
			}
			index_right = index_right + cellRank * _maxNodePerCell;
			// apply tension force from right
			if (_isActiveAddr[index_right]) {
				double posX = _locXAddr[index];
				double posY = _locYAddr[index];
				double vec1X = _locXAddr[index_right] - posX;
				double vec1Y = _locYAddr[index_right] - posY;
				double vec2X = centerX - posX;
				double vec2Y = centerY - posY;
				//double result = fabs(vec1X * vec2Y - vec2X * vec1Y) / 2.0;
				double result = (vec1X * vec2Y - vec2X * vec1Y) / 2.0;
				// if (result >= 0){
					return result;
				// }
				// else{
				// 	return -result;
				// }
			} else {
				return 0.0;
			}
		}
	}
};


struct BC_Tissue_Damp: public thrust::unary_function<CVec3,CVec2> {
	double _TMinX, _TMaxX,_TMinY,_TMaxY,_Damp_Coef ; 
        int    _NumActCells ; 
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__  BC_Tissue_Damp(double InputFunctor1, double InputFunctor2, double InputFunctor3
                                          , double InputFunctor4, double InputFunctor5, int InputFunctor6
			) :
			_TMinX(InputFunctor1), _TMaxX(InputFunctor2)
                       ,_TMinY(InputFunctor3), _TMaxY(InputFunctor4), _Damp_Coef(InputFunctor5),_NumActCells(InputFunctor6) {
	}
	__host__ __device__ CVec2 operator()(const CVec3 &inputInfo) {
		double CenterCellX = thrust::get<0>(inputInfo);
		double CenterCellY = thrust::get<1>(inputInfo);
                double TCenterX= 0.5*(_TMinX+_TMaxX);
                double TCenterY= 0.5*(_TMinY+_TMaxY); 
                double TRadius=0.5*( 0.5*(_TMaxX-_TMinX) +0.5*(_TMaxY-_TMinY)) ; 
                
                if (_NumActCells>50) {                  

                double Dist=sqrt (
                            (CenterCellX-TCenterX)*(CenterCellX-TCenterX)+
                           (CenterCellY-TCenterY)*(CenterCellY-TCenterY)) ; 
                double Damp=_Damp_Coef + max(0.0,Dist/TRadius-0.8)*1.0/(1.0-0.8)*0*_Damp_Coef     ;     // I made it inactive         
                        
			return thrust::make_tuple(CenterCellX,Damp);
		}
                else { 
                        return thrust::make_tuple(CenterCellX,_Damp_Coef);
                     }

}
}; 


/**struct BC_Tissue_Damp: public thrust::unary_function<CVec2,CVec2> {
	double _Damp_Coef ; 
	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
	__host__ __device__  BC_Tissue_Damp(double InputFunctor1
			) :
			 _Damp_Coef(InputFunctor1) {
	}
	__host__ __device__ CVec2 operator()(const CVec2 &inputInfo) {
		double CenterCellX = thrust::get<0>(inputInfo);
		double CenterCellY = thrust::get<1>(inputInfo);
         //       double TCenterX= 0.5*(_TMinX+_TMaxX);
           //     double TCenterY= 0.5*(_TMinY+_TMaxY); 
             //   double TRadius=0.5*( 0.5*(_TMaxX-_TMinX) +0.5*(_TMaxY-_TMinY)) ; 

               // double Dist=sqrt (
                 //           (CenterCellX-TCenterX)*(CenterCellX-TCenterX)+
                   //        (CenterCellY-TCenterY)*(CenterCellY-TCenterY)) ; 
                //double Damp=_Damp_Coef + max(0.0,Dist/TRadius-0.8)*1.0/(1.0-0.8)*200*_Damp_Coef     ;              
                        
			return thrust::make_tuple(CenterCellX,CenterCellY);
		}
}; 

**/


struct CalPerim: public thrust::unary_function<Tuuudd, double> {
 	uint _maxNodePerCell;
 	bool* _isActiveAddr;
 	double* _locXAddr;
 	double* _locYAddr;
 	// comment prevents bad formatting issues of __host__ and __device__ in Nsight
 	__host__ __device__ CalPerim(uint maxNodePerCell, bool* isActiveAddr,
 			double* locXAddr, double* locYAddr) :
 			_maxNodePerCell(maxNodePerCell), _isActiveAddr(isActiveAddr), _locXAddr(
 					locXAddr), _locYAddr(locYAddr) {
 	}
 	__device__
 	double operator()(const Tuuudd &inputData) const {
 		uint activeMembrCount = thrust::get<0>(inputData);
 		uint cellRank = thrust::get<1>(inputData);
 		uint nodeRank = thrust::get<2>(inputData);
 		double centerX = thrust::get<3>(inputData);
 		double centerY = thrust::get<4>(inputData);
 		uint index = cellRank * _maxNodePerCell + nodeRank;
 
 		if (_isActiveAddr[index] == false || nodeRank >= activeMembrCount ) {
 			return 0.0;
 		} else {
 			int index_right = nodeRank + 1;
 			if (index_right == (int) activeMembrCount) {
 				index_right = 0;
 			}
 			index_right = index_right + cellRank * _maxNodePerCell;
 			// apply tension force from right
 			if (_isActiveAddr[index_right]) {
 				double posX = _locXAddr[index];
 				double posY = _locYAddr[index];
 				double vec1X = _locXAddr[index_right] - posX;
 				double vec1Y = _locYAddr[index_right] - posY;
 				//double vec2X = centerX - posX;
 				//double vec2Y = centerY - posY;
 				double result = sqrt(vec1X * vec1X + vec1Y * vec1Y);
 				return result;
 			} else {
 				return 0.0;
 			}
 		}
 	}
 };
 

struct CellInfoVecs {
	/**
	 * @param growthProgress is a vector of size maxCellCount.
	 * In each cell, \n
	 * progress == 0 means recently divided
	 * progress == 1 means ready to divide
	 */
	//ChangesMadeByKT_begin
	thrust::device_vector<int> cellSubdomainIndx;
	//ChangesMadeByKT_end
	thrust::device_vector<int> daughterCellProduced;

	thrust::device_vector<double> distFromBasalLoc;
	thrust::device_vector<double> distFromApicalLoc; 
	 bool isOneTimeStepPostDivision = false;// = false;
	 bool isTwoTimeStepPostDivision = false;
	bool isPostDivision = false;// = false;
	bool isPostAddMembrNodes = false;
	thrust::device_vector<MembraneType1> maxTenIndxTypeVec;
	thrust::device_vector<double> cellAreaGrowthProgress;
	thrust::device_vector<double> cellAreaGrowthProgressNonMitotic;
	thrust::device_vector<double> contractileSpringGrowthProgress;
	thrust::device_vector<double> growthProgress; //Ali
	thrust::device_vector<double> Cell_Time;//Ali
	thrust::device_vector<double> Cell_Damp;//Ali
	thrust::device_vector<int> cellRoot;//Ali
	thrust::device_vector<int> numApicalVec;
	thrust::device_vector<int> numBasalVec;
	thrust::device_vector<int> cellRankVec;
	thrust::device_vector<double> distFromNucleus_normal;
	thrust::device_vector<double> distFromNucleus_normal_apical;
	thrust::device_vector<double> individualCellHeight;
	thrust::device_vector<double> individualCellHeight_springHeight;
	thrust::device_vector<double> contractActomyo_multip_perCell;
	thrust::device_vector<double> contractActomyo_multip_apical_perCell;
       
	thrust::device_vector<double> growthProgressOld;  //A&A
//Ali
        
//Ali
	thrust::device_vector<double> expectedLength;
//thrust::device_vector<double> currentLength;
	thrust::device_vector<double> lengthDifference;
// array to hold temp value computed in growth phase.
// obtained by smallest value of vector product of (a cell node to the cell center)
// and (growth direction). This will be a negative value
	thrust::device_vector<double> smallestDistance;
// biggest value of vector product of (a cell node to the cell center)
// and (growth direction). This will be a positive value
	thrust::device_vector<double> biggestDistance;
	thrust::device_vector<uint> activeNodeCountOfThisCell;
	thrust::device_vector<double> lastCheckPoint;
	thrust::device_vector<bool> isDividing;
	thrust::device_vector<bool> isEnteringMitotic; //A&A

	//thrust::device_vector<bool> isRemoving;//AAMIRI

// This cell type array should be initialized together with the host class.
	thrust::device_vector<SceNodeType> cellTypes;
	thrust::device_vector<bool> isScheduledToGrow;
	thrust::device_vector<bool> isScheduledToShrink;//AAMIRI
	thrust::device_vector<bool> isCellActive;//AAMIRI
	thrust::device_vector<double> centerCoordX;
	thrust::device_vector<double> InternalAvgX;
	//thrust::device_vector<double> InternalAvgIniX;
	thrust::device_vector<double> tmpShiftVecX;
	thrust::device_vector<double> centerCoordY;
	thrust::device_vector<double> InternalAvgY;
	//thrust::device_vector<double> InternalAvgIniY;
	thrust::device_vector<double> tmpShiftVecY;
	thrust::device_vector<double> centerCoordZ;
	thrust::device_vector<double> apicalLocX; //Ali 
	thrust::device_vector<double> apicalLocY; //Ali

	thrust::device_vector<double> basalLocX; //Ali 
	thrust::device_vector<double> basalLocY; //Ali 
	thrust::device_vector<int>    eCMNeighborId; //Ali 

	thrust::device_vector<double> nucleusLocX; //Ali 
	thrust::device_vector<double> nucleusLocY; //Ali
	thrust::device_vector<double> nucleusDesireLocX; //Ali 
	thrust::device_vector<double> nucleusDesireLocY; //Ali 
	thrust::device_vector<double> nucDesireDistApical; //Ali 
	thrust::device_vector<double> nucleusLocPercent; //Ali 
	thrust::device_vector<double> cellCenterPerturbedLocLocX; //Kevin
	thrust::device_vector<double> cellCenterPerturbedLocLocY; //Kevin
	thrust::device_vector<double> cellCenterDesireDistApical; //Kevin
	thrust::device_vector<double> sumLagrangeFPerCellX; //Ali 
	thrust::device_vector<double> sumLagrangeFPerCellY; //Ali 
	thrust::device_vector<double> sumLagrangeFN; //Ali 
	thrust::device_vector<double> sumF_MI_M_N; //Ali 
	thrust::device_vector<int> apicalNodeCount; //Ali 
	thrust::device_vector<int> basalNodeCount; //Ali 
	thrust::device_vector<int> ringApicalId; //Ali 
	thrust::device_vector<int> ringBasalId; //Ali 

	thrust::device_vector<double> HertwigXdir; //A&A
	thrust::device_vector<double> HertwigYdir; //A&A


	thrust::device_vector<bool> isRandGrowInited;
	thrust::device_vector<double> growthSpeed;
	thrust::device_vector<double> growthXDir;
	thrust::device_vector<double> growthYDir;
// some memory for holding intermediate values instead of dynamically allocating.
	thrust::device_vector<uint> cellRanksTmpStorage;
	thrust::device_vector<uint> cellRanksTmpStorage1;  //Ali

	thrust::device_vector<uint> activeMembrNodeCounts;
	thrust::device_vector<uint> activeIntnlNodeCounts;

	thrust::device_vector<double> membrGrowProgress;
	thrust::device_vector<double> membrGrowSpeed;
	thrust::device_vector<double> maxTenRiVec;
	thrust::device_vector<double> maxDistToRiVec;  //Ali 
	thrust::device_vector<double> minDistToRiVec;  //Ali 
	thrust::device_vector<double> maxTenRiMidXVec;
	thrust::device_vector<double> maxTenRiMidYVec;
	thrust::device_vector<double> aveTension;
	thrust::device_vector<uint> maxTenIndxVec;
	thrust::device_vector<uint> minTenIndxVec; //Ali 
	thrust::device_vector<bool> isMembrAddingNode;
	thrust::device_vector<bool> isMembrRemovingNode; // Ali

	thrust::device_vector<double> cellAreaVec;
    thrust::device_vector<double> cellPerimVec;//AAMIRI
    thrust::device_vector<double> cellPressure;//Ali 
    thrust::device_vector<ECellType> eCellTypeV2 ;//Ali
    //thrust::host_vector<ECellType> eCellTypeV2Host ;//Ali
};

struct CellNodeInfoVecs {
// some memory for holding intermediate values instead of dynamically allocating.
	thrust::device_vector<uint> cellRanks;
	thrust::device_vector<double> activeXPoss;
	thrust::device_vector<double> activeYPoss;
	thrust::device_vector<double> activeZPoss;
	thrust::device_vector<double> activeLocXApical; //Ali 
	thrust::device_vector<double> activeLocYApical; //Ali 

	thrust::device_vector<double> activeLocXBasal; //Ali 
	thrust::device_vector<double> activeLocYBasal; //Ali 
// temp value for holding a node direction to its corresponding center
	thrust::device_vector<double> distToCenterAlongGrowDir;
};

struct CellGrowthAuxData {
	double prolifDecay;

	double randomGrowthSpeedMin_Ori;
	double randomGrowthSpeedMax_Ori;

	double randomGrowthSpeedMin;
	double randomGrowthSpeedMax;

	double grthPrgrCriVal_M_Ori;
	double grthProgrEndCPU;
// we need help from this parameter to generate better quality pseduo-random numbers.
	uint randGenAuxPara;

	double fixedGrowthSpeed;

	double* growthFactorMagAddress;
	double* growthFactorDirXAddress;
	double* growthFactorDirYAddress;

// obtain pointer address for second region
	double* growthFactorMagAddress2;
	double* growthFactorDirXAddress2;
	double* growthFactorDirYAddress2;

	uint totalNodeCountForActiveCells;

	bool* nodeIsActiveAddress;
	double* nodeXPosAddress;
	double* nodeYPosAddress;
	MembraneType1* memNodeType1Address  ; //Ali
	int* adhIndxAddr;
};

struct CellDivAuxData {
// ************************ these parameters are used for cell division *************************
// sum all bool values which indicate whether the cell is going to divide.
// toBeDivideCount is the total number of cells going to divide.
	int cellRank_division;
	int cellRank_division2;
	uint toEnterMitoticCount ; //A&A
	uint toBeDivideCount;
	uint nodeStorageCount;
	double targetCellDividingArea;

	thrust::device_vector<double> tmpApicalLoc;
	thrust::device_vector<double> tmpBasalLoc;

	thrust::device_vector<int> tmpNodeMemMirrorIndex_M;

	//uint toBeRemovedCount;//AAMIRI

	thrust::device_vector<bool> tmpIsActiveHold1;
	thrust::device_vector<double> tmpDistToCenter1;
	thrust::device_vector<uint> tmpCellRankHold1;
	thrust::device_vector<double> tmpXValueHold1;
	thrust::device_vector<double> tmpYValueHold1;
	thrust::device_vector<double> tmpZValueHold1;

	thrust::device_vector<bool> tmpIsActiveHold2;
	thrust::device_vector<double> tmpDistToCenter2;
	thrust::device_vector<double> tmpXValueHold2;
	thrust::device_vector<double> tmpYValueHold2;
	thrust::device_vector<double> tmpZValueHold2;

	thrust::device_vector<SceNodeType> tmpCellTypes;
// ************************ these parameters are used for cell division *************************

	thrust::device_vector<uint> tmpCellRank_M;
	thrust::device_vector<double> tmpDivDirX_M;
	thrust::device_vector<double> tmpDivDirY_M;
	thrust::device_vector<double> tmpCenterPosX_M;
	thrust::device_vector<double> tmpCenterPosY_M;
	thrust::device_vector<double> tmpIntAvgX_M; //Ali 
	thrust::device_vector<double> tmpIntAvgY_M;//Ali 
	thrust::device_vector<double> tmpNucleusCenterPosX_M;
	thrust::device_vector<double> tmpNucleusCenterPosY_M;

	thrust::device_vector<bool> tmpIsActive_M;
	thrust::device_vector<double> tmpNodePosX_M;
	thrust::device_vector<double> tmpNodePosY_M;
	thrust::device_vector<MembraneType1> tmpNodeType ; //Ali 

	thrust::device_vector<bool> tmpIsActiveHost_M;
	thrust::device_vector<double> tmpNodePosXHost_M;
	thrust::device_vector<double> tmpNodePosYHost_M;

	thrust::device_vector<bool> tmpIsActive1_M;
	thrust::device_vector<double> tmpXPos1_M;
	thrust::device_vector<double> tmpYPos1_M;
	thrust::device_vector<MembraneType1> tmpNodeType1 ; //Ali 

	thrust::device_vector<bool> tmpIsActive2_M;
	thrust::device_vector<double> tmpXPos2_M;
	thrust::device_vector<double> tmpYPos2_M;
	thrust::device_vector<MembraneType1> tmpNodeType2 ; //Ali 

	thrust::device_vector<double> tmpHertwigXdir;  //A&A
	thrust::device_vector<double> tmpHertwigYdir;  //A&A
	thrust::host_vector<bool> isMotherCellBehind ;  //Ali 

	std::vector<CVector> tmp1IntnlVec, tmp2IntnlVec;
	std::vector<CVector> tmp1VecMem, tmp2VecMem ; 
	std::vector<MembraneType1> tmp1VecMemNodeType, tmp2VecMemNodeType; //Ali 
	std::vector<uint> tmp1MemActiveCounts, tmp1InternalActiveCounts;
	std::vector<uint> tmp2MemActiveCounts, tmp2InternalActiveCounts;

	uint cellRankMother;
	uint cellRankDaughter;
};

struct CellPrintOnlyAuxData {
// ************************ these parameters are used for cell division *************************
// sum all bool values which indicate whether the cell is going to divide.
// toBeDivideCount is the total number of cells going to divide.
	int cellRank_division;
	int cellRank_division2;
	uint toEnterMitoticCount ; //A&A
	uint toBeDivideCount;
	uint nodeStorageCount;

	thrust::device_vector<bool> isDividing;

	thrust::device_vector<double> tmpApicalLoc;
	thrust::device_vector<double> tmpBasalLoc;

	thrust::device_vector<int> tmpNodeMemMirrorIndex_M;

	//uint toBeRemovedCount;//AAMIRI

	thrust::device_vector<bool> tmpIsActiveHold1;
	thrust::device_vector<double> tmpDistToCenter1;
	thrust::device_vector<uint> tmpCellRankHold1;
	thrust::device_vector<double> tmpXValueHold1;
	thrust::device_vector<double> tmpYValueHold1;
	thrust::device_vector<double> tmpZValueHold1;

	thrust::device_vector<bool> tmpIsActiveHold2;
	thrust::device_vector<double> tmpDistToCenter2;
	thrust::device_vector<double> tmpXValueHold2;
	thrust::device_vector<double> tmpYValueHold2;
	thrust::device_vector<double> tmpZValueHold2;

	thrust::device_vector<SceNodeType> tmpCellTypes;
// ************************ these parameters are used for cell division *************************

	thrust::device_vector<uint> tmpCellRank_M;
	thrust::device_vector<double> tmpDivDirX_M;
	thrust::device_vector<double> tmpDivDirY_M;
	thrust::device_vector<double> tmpCenterPosX_M;
	thrust::device_vector<double> tmpCenterPosY_M;
	thrust::device_vector<double> tmpIntAvgX_M; //Ali 
	thrust::device_vector<double> tmpIntAvgY_M;//Ali 
	thrust::device_vector<double> tmpNucleusCenterPosX_M;
	thrust::device_vector<double> tmpNucleusCenterPosY_M;

	thrust::device_vector<bool> tmpIsActive_M;
	thrust::device_vector<double> tmpNodePosX_M;
	thrust::device_vector<double> tmpNodePosY_M;
	thrust::device_vector<MembraneType1> tmpNodeType ; //Ali 

	thrust::device_vector<bool> tmpIsActiveHost_M;
	thrust::device_vector<double> tmpNodePosXHost_M;
	thrust::device_vector<double> tmpNodePosYHost_M;

	thrust::device_vector<bool> tmpIsActive1_M;
	thrust::device_vector<double> tmpXPos1_M;
	thrust::device_vector<double> tmpYPos1_M;
	thrust::device_vector<MembraneType1> tmpNodeType1 ; //Ali 

	thrust::device_vector<bool> tmpIsActive2_M;
	thrust::device_vector<double> tmpXPos2_M;
	thrust::device_vector<double> tmpYPos2_M;
	thrust::device_vector<MembraneType1> tmpNodeType2 ; //Ali 

	thrust::device_vector<double> tmpHertwigXdir;  //A&A
	thrust::device_vector<double> tmpHertwigYdir;  //A&A
	thrust::host_vector<bool> isMotherCellBehind ;  //Ali 

	std::vector<CVector> tmp1IntnlVec, tmp2IntnlVec;
	std::vector<CVector> tmp1VecMem, tmp2VecMem ; 
	std::vector<MembraneType1> tmp1VecMemNodeType, tmp2VecMemNodeType; //Ali 
	std::vector<uint> tmp1MemActiveCounts, tmp1InternalActiveCounts;
	std::vector<uint> tmp2MemActiveCounts, tmp2InternalActiveCounts;

	uint cellRankMother;
	uint cellRankDaughter;
};

struct MembrPara {
	double membrStiffCPU;
	double membrStiff_Mitotic;
	double kContractMemb ;  // Ali 
	double membrEquLenCPU;
	double membrGrowCoeff_Ori;
	double membrGrowLimit_Ori;
	double membrGrowCoeff;
	double membrGrowLimit;
	double membrBendCoeff;
	double membrBendCoeff_Mitotic;
	double adjustLimit;
	double adjustCoeff;

	double growthConst_N;
	uint initMembrCt_N;
	uint initIntnlCt_N;
	void initFromConfig();
        double F_Ext_Incline ; 
};

/**
 * Modified implementation of subcellular element.
 * Important component to process cell growth and division.
 * Boundary, epithilum layer and ECM are also treated as cells but computed seperately.
 * @param beginPosOfBdry   represents begining position of boundary.
 * @param maxNodeOfBdry    represents maximum number of nodes of boundary.
 * @param beginPosOfEpi    represents begining position of epithilum layer.
 * @param maxNodeOfEpi     represents maximum number of nodes of epithilum layer.
 * @param maxNodeOfECM     represents maximum number of nodes per ECM
 * @param beginPosOfECM    represents begining position of ECM.
 * @param maxECMCount      represents maximum number of ECM.
 * @param maxNodeOfOneCell represents maximum number of nodes per cell
 * @param beginPosOfCells  represents begining position of cells.
 * @param maxCellCount     represents maximum number of cells.
 * @param isDivideCrticalRatio If the current cell length divide
 * CellFinalLength is larger than this ratio and the cell growth progress
 *  is complete then we set cell ready to divide
 */
class SceCells {
	SceNodes* nodes;
	SceECM  *eCMPointerCells;  //Ali
	Solver  *solverPointer; 
	NodeAllocPara allocPara;
	SceMiscPara miscPara;
	SceBioPara bioPara;
	CellInfoVecs cellInfoVecs;
	CellNodeInfoVecs cellNodeInfoVecs;
	CellGrowthAuxData growthAuxData;
	CellDivAuxData divAuxData;
	CellPrintOnlyAuxData printAuxData;
	ControlPara controlPara;

	NodeAllocPara_M allocPara_m;
	MembrPara membrPara;

// in this class, there are a lot of arrays that store information for each cell
// this counting iterator is used for all these arrays indicating the begining.
	thrust::counting_iterator<uint> countingBegin;
	thrust::constant_iterator<uint> initIntnlNodeCount;
	thrust::constant_iterator<double> initGrowthProgress;

	uint totalNodeCountForActiveCells;
	
	double dt;
	bool isInitNucPercentCalculated ; 
	bool isBasalActinPresent ; 
	bool isCellGrowSet ; 
	bool addNode  ; 
    double Damp_Coef ;   //Ali
    double InitTimeStage ;  //A & A 
	int freqPlotData ;
	double centerShiftRatio;
	double shrinkRatio;
	double memNewSpacing;
	double curTime;
	int relaxCount ;  //Ali 
	int lastPrintNucleus ; 
	int outputFrameNucleus ; 
	void readMiscPara();
	void readBioPara();
	void writeNucleusIniLocPercent() ; 
	void readNucleusIniLocPercent() ; 
	void copyInitActiveNodeCount(
			std::vector<uint>& numOfInitActiveNodesOfCells);
	void copyInitActiveNodeCount_M(std::vector<uint>& initMembrActiveNodeCounts,
			std::vector<uint>& initIntnlActiveNodeCounts,
			std::vector<double> &initGrowProgVec,
			std::vector<ECellType> & eCellTypeV1); //Ali 

	void initCellInfoVecs();
	void initCellNodeInfoVecs();
	void initGrowthAuxData();
	void initGrowthAuxData_M();
	void initialize(SceNodes* nodesInput);
	void initialize_M(SceNodes* nodesInput, SceECM* eCMInput, Solver *solver);

	void distributeBdryIsActiveInfo();
	void distributeProfileIsActiveInfo();
	void distributeECMIsActiveInfo();
	void distributeCellIsActiveInfo();

	void distributeCellGrowthProgress();

	void distributeIsCellRank();

	void allComponentsMove();

	void growAtRandom(double d_t);


	void growAlongX(bool isAddPt, double d_t);
	void growWithStress(double d_t);

	void randomizeGrowth();
	void setGrowthDirXAxis();

	void computeCenterPos();
        void BC_Imp_M() ; 
	void divide2DSimplified();

	/**
	 * Use the growth magnitude and dt to update growthProgress.
	 */
	void updateGrowthProgress();

	/**
	 * Decide if the cells are going to add a node or not.
	 * Use lastCheckPoint and growthProgress to decide whether add point or not
	 */
	void decideIsScheduleToGrow();

	/**
	 * Calculate target length of cell given the cell growth progress.
	 * length is along the growth direction.
	 */
	void computeCellTargetLength();

	/**
	 * Compute distance of each node to its corresponding cell center.
	 * The distantce could be either positive or negative, depending on the pre-defined
	 * growth direction.
	 */
	void computeDistToCellCenter();

	/**
	 * For nodes of each cell, find the maximum and minimum distance to the center.
	 * We will then calculate the current length of a cell along its growth direction
	 * using max and min distance to the center.
	 */
	void findMinAndMaxDistToCenter();

	/**
	 * Compute the difference for cells between their expected length and current length.
	 */
	void computeLenDiffExpCur();

	/**
	 * Use the difference that just computed and growthXDir&growthYDir
	 * to apply stretching force (velocity) on nodes of all cells
	 */
	void stretchCellGivenLenDiff();

	/**
	 * This is just an attempt. Cells move according to chemicals.
	 */
	void cellChemotaxis();

	/**
	 * Adjust the velocities of nodes.
	 * For example, velocity of boundary nodes must be zero.
	 */
	void adjustNodeVel();

	/**
	 * Move nodes according to the velocity we just adjusted.
	 */
	void moveNodes();

	/**
	 * Add a point to a cell if it is scheduled to grow.
	 * This step does not guarantee success ; If adding new point failed, it will not change
	 * isScheduleToGrow and activeNodeCount;
	 */
	void addPointIfScheduledToGrow();

	/**
	 * 2D version of cell division.
	 * Division process is done by creating two temporary vectors to hold the node information
	 * that are going to divide.
	 *
	 * step 1: based on lengthDifference, expectedLength and growthProgress,
	 *     this process determines whether a certain cell is ready to divide and then assign
	 *     a boolean value to isDivided.
	 *
	 * step 2. copy those cells that will divide in to the temp vectors created
	 *
	 * step 3. For each cell in the temp vectors, we sort its nodes by its distance to the
	 * corresponding cell center.
	 * This step is not very effcient when the number of cells going to divide is big.
	 * but this is unlikely to happen because cells will divide according to external chemical signaling
	 * and each will have different divide progress.
	 *
	 * step 4. copy the right part of each cell of the sorted array (temp1) to left part of each cell of
	 * another array
	 *
	 * step 5. transform isActive vector of both temp1 and temp2, making only left part of each cell active.
	 *
	 * step 6. insert temp2 to the end of the cell array
	 *
	 * step 7. copy temp1 to the previous position of the cell array.
	 *
	 * step 8. add activeCellCount of the system.
	 *
	 * step 9. mark isDivide of all cells to false.
	 */

	bool decideIfGoingToDivide();

	void copyCellsPreDivision();

	void sortNodesAccordingToDist();

	void copyLeftAndRightToSeperateArrays();

	void transformIsActiveArrayOfBothArrays();

	void addSecondArrayToCellArray();

	void copyFirstArrayToPreviousPos();

	void updateActiveCellCount();

	void markIsDivideFalse();

	/**
	 * This is different from the default set function.
	 */
	void setCellTypes(thrust::device_vector<SceNodeType> cellTypesInput) {
		thrust::copy(cellTypesInput.begin(), cellTypesInput.end(),
				cellInfoVecs.cellTypes.begin());
	}

	void distributeIsActiveInfo();

	void applyMemForce_M(bool cellPolar, bool subCellPolar);
	void applyVolumeConstraint(double timeRatio, double timeRatio_Crit_Division, double volume_Increase_Target_Ratio, double volume_Increase_Scale, double postDivision_restorationRateScale, int cycle);
	void ApplyExtForces();
	// void computeLagrangeForces();
	void computeLagrangeForces(double timeRatio, double volume_Increase_Target_Ratio);
	void computeContractileRingForces();

	void applySceCellDisc_M();

	// void applyMembContraction(double timeRatio, double timeRatio_Crit_actomyo, double timeRatio_Crit_Division, double distFromNucleus_max, double distFromNucleus_min, double percentage_before_timeRatio_Crit_Division_scaling) ; 
	void applyMembContraction2(double timeRatio, double timeRatio_Crit_actomyo, double timeRatio_Crit_Division, double distFromNucleus_max, double distFromNucleus_min, double mitoRndActomyoStrengthScaling);//double percentage_before_timeRatio_Crit_Division_scaling) ; 
	void computeInternalAvgPos_M();
	void computeInternalMaxMinPos_M();
	void computeCenterPos_M2();

	// void growAtRandom_M(double dt);
	void growAtRandom_M(double growthProgressSpeed);
	void growAtRandom_M_Ver2(double growthProgressSpeed, double mitoticThreshold);


	void assignMemNodeType();  //Ali 
	void computeApicalLoc(double timeRatio, double timeRatio_Crit_Division);  //Ali 
	void computeBasalLoc();  //Ali 
	void computeNucleusLoc();  //Ali 
	void computeNucleusDesireLoc();  //Ali 
	void computeCellCenterPerturbedLoc(); //Kevin
	void computeNucleusIniLocPercent();  //Ali 
	void computeIndividualCellHeight(double distFromNucleus_normalMax1,double distFromNucleus_normalMax2,double distFromNucleus_normalMax3,
									 double distFromNucleus_normalMax_apical1,double distFromNucleus_normalMax_apical2,double distFromNucleus_normalMax_apical3); //Kevin T. 2021/07/17
	void computeIndividualCellHeight_Ver2();
	void applyForceInteractionNucleusAsPoint() ; //Ali 
	void updateInternalAvgPosByNucleusLoc_M();  //Ali 
	void PlotNucleus(int & lastPrintNucleus, int & outputFrameNucleus);  //Ali 

	void enterMitoticCheckForDivAxisCal(double mitoticThreshold);
	void divide2D_M(double volume_Increase_Target_Ratio, double timeRatio, double thresholdToIntroduceNewCell);

	void distributeCellGrowthProgress_M();

	void StoreNodeOldPositions() ; 
	void allComponentsMove_M();

	void allComponentsMoveImplicitPart() ;
	void CalRHS() ;
    void EquMotionCoef(vector<int> & indexPrev, vector<int> & indexNext);
    void UpdateLocations(const vector<int> & indexPrev, const vector<int> & indexNext); 
	
	void randomizeGrowth_M();

	// void updateGrowthProgress_M();

	void updateGrowthProgress_M(double growthProgressSpeed);
	void updateGrowthProgress_M_Ver2(double growthProgressSpeed, double mitoticThreshold);

	void decideIsScheduleToGrow_M();

	void decideIsScheduleToShrink_M();//AAMIRI

	void computeCellTargetLength_M();

	void computeDistToCellCenter_M();

	void findMinAndMaxDistToCenter_M();

	void computeLenDiffExpCur_M();

	void stretchCellGivenLenDiff_M();

	void addPointIfScheduledToGrow_M();

	void delPointIfScheduledToGrow_M();//AAMIRI

	void findTangentAndNormal_M();//AAMIRI

	/**
	 * It is possible for cells to have node number that is less than expect after division.
	 * This adjustment is necessary for cells to grow normally.
	 */
	void adjustGrowthInfo_M();

	void copyCellsPreDivision_M();
	void copyCellsForPrintingOnly_M();
	void copyCellsEnterMitotic(); //A&A
	void copyCellsEnterDivision();
        void findHertwigAxis(); //A&A 
		void findHertwigAxis_useBasalApicalLoc();
	void createTwoNewCellArr_M();
	void printCellCenterLine_M(int p);
	void copyFirstCellArr_M(double quiescene1, double quiescence1_half);
	void copySecondCellArr_M(double quiescene2, double quiescence2_half);
	void updateActiveCellCount_M();
	void markIsDivideFalse_M();

	//void removeCellArr_M();//AAMIRI
	//void updateActiveCellCountAfterRemoval_M();//AAMIRI

	void adjustNodeVel_M();
	void moveNodes_M();
	void moveNodes_BC_M();

	void readMiscPara_M();
	void initCellInfoVecs_M();
	void initCellNodeInfoVecs_M();

	void updateMembrGrowthProgress_M();
	void handleMembrGrowth_M(int maxApicalBasalNodeNum, double maxLengthToAddMemNodes);

	void copyToGPUConstMem();

	void myDebugFunction();
	void divDebug();
	void membrDebug();

	void calMembrGrowSpeed_M();
	/**
	 * if cell is under compression, its area will not be less than expected.
	 * growth speed is adjusted by sqrt(area) and circumference ratio.
	 */
	void adjustMembrGrowSpeed_M();
	void decideIfAddMembrNode_M(int maxApicalBasalNodeNum, double maxLengthToAddMemNodes);
	void decideIfDelMembrNode_M(); // Ali
	void addMembrNodes_M();
	void delMembrNodes_M(); // Ali

	bool tmpDebug;

	bool decideIfGoingToDivide_M(double volume_Increase_Target_Ratio);
        bool decideIfAnyCellEnteringMitotic(double mitoticThreshold);//A&A 
//	bool decideIfGoingToRemove_M();//AAMIRI

	void assembleVecForTwoCells(uint i);
	void shiftIntnlNodesByCellCenter(CVector intCell1Center, CVector intCell2Center); //Ali modified
	// void processMemVec(uint i, std::vector<VecValT>& tmp1, std::vector<VecValT>& tmp2);
	void processMemVec(uint i, std::vector<VecValT>& tmp1, std::vector<VecValT>& tmp2, CVector oldNucleusCenter);
	void processMemVec_Ver2(uint i, std::vector<VecValT>& tmp1, std::vector<VecValT>& tmp2, CVector oldNucleusCenter,
						std::vector<CVector>& cellCenterLine_Basal2Apical,
						std::vector<CVector>& cellCenterLine_Apical2Basal,
						std::vector<CVector>& cellCenterLine_Basal2Apical_leftShift,
						std::vector<CVector>& cellCenterLine_Basal2Apical_rightShift,
						std::vector<CVector>& cellCenterLine_Apical2Basal_leftShift,
						std::vector<CVector>& cellCenterLine_Apical2Basal_rightShift,
						std::vector<double>& cellCenterLine_MirrorLength_Basal2Apical,
						std::vector<double>& cellCenterLine_MirrorLength_Apical2Basal);
	void obtainMembrAndIntnlNodes(uint i, vector<CVector>& membrNodes,
			vector<CVector>& intnlNodes);
	void obtainMembrAndIntnlNodesPlusNodeType(uint i, vector<CVector>& membrNodes,
			vector<CVector>& intnlNodes, vector<MembraneType1>& nodeTypeIndxDiv); //Ali modified

	void obtainMembrAndIntnlNodesPlusNodeType2(uint i, vector<CVector>& membrNodes,
			vector<CVector>& intnlNodes, vector<MembraneType1>& nodeTypeIndxDiv, 
			vector<CVector>& cellCenterLine_Basal2Apical, vector<CVector>& cellCenterLine_Apical2Basal, 
			vector<CVector>& cellCenterLine_Basal2Apical_leftShift, vector<CVector>& cellCenterLine_Basal2Apical_rightShift,
			vector<CVector>& cellCenterLine_Apical2Basal_leftShift, vector<CVector>& cellCenterLine_Apical2Basal_rightShift,
			vector<double>& cellCenterLine_MirrorLength_Basal2Apical,
			vector<double>& cellCenterLine_MirrorLength_Apical2Basal); //Kevin
	void obtainMembrAndIntnlNodesPlusNodeType2_printingOnly(uint i, vector<CVector>& membrNodes,
		vector<CVector>& intnlNodes, vector<MembraneType1> & nodeTypeIndxDiv, 
		vector<CVector>& cellCenterLine_Basal2Apical, vector<CVector>& cellCenterLine_Apical2Basal);
	//CVector obtainCenter(uint i);
	CVector obtainCellCenter(uint i); //Ali 
	CVector obtainNucleusCenter(uint i, vector<CVector> IntnlNodes);
	CVector obtainIntCenter(uint i); //Ali 
	CVector calDivDir_MajorAxis(CVector oldCenter, vector<CVector>& membrNodes,
			double& lenAlongMajorAxis);

	std::pair <int, int>  calApicalBasalRingIds (CVector divDir, CVector oldCellCenter, vector<CVector>& membrNodes, vector<MembraneType1> & nodeTypeIndxDiv);
	CVector calDivDir_ApicalBasal(CVector oldCellCenter, vector<CVector>& membrNodes,
			double& lenAlongMajorAxis, vector<MembraneType1> & nodeTypeIndxDiv);
	double calLengthAlongHertwigAxis(CVector divDir, CVector oldCellCenter, vector<CVector>& membrNodes); //A&A

	void obtainTwoNewIntCenters(CVector& oldIntCenter, CVector& divDir,
			double lenAlongHertwigAxis, CVector& intCenterNew1, CVector& intCenterNew2); //A& A  modified
	void prepareTmpVec(uint i, CVector divDir, CVector oldCellCenter,CVector oldIntCenter 
			,std::vector<VecValT>& tmp1, std::vector<VecValT>& tmp2); //Ali 

	void calCellArea();
    void calCellPerim();//AAMIRI
    void calCellPressure();//AAMIRI
	// void eCMCellInteraction(bool cellPolar, bool subCellPolar, bool tmpIsInitSetup, double timeRatio, double timeRatio_Crit_ECM, double timeRatio_Crit_Division, int relaxCount) ;
	void eCMCellInteraction(bool cellPolar, bool subCellPolar, bool tmpIsInitSetup, double timeRatio, double timeRatio_Crit_ECM, double timeRatio_Crit_Division, int relaxCount, double mitoticThreshold) ; 
public:

	SceCells();

	SceCells(SceNodes* nodesInput,
			std::vector<uint> &numOfInitActiveNodesOfCells,
			std::vector<SceNodeType> &cellTypes);

	SceCells(SceNodes* nodesInput, SceECM * eCMInput,Solver *solver,
			std::vector<uint> &numOfInitActiveMembrNodeCounts,
			std::vector<uint> &numOfInitActiveIntnlNodeCounts,
			std::vector<double> &initGrowProgVec, std::vector<ECellType> &eCellTypeV1 
			,double InitTimeStage);

	CellInfoVecs  &  getCellInfoVecs()   {
			return cellInfoVecs ; 
	}; // Ali 
    //void UpdateTimeStepByAdaptiveMethod(double adaptiveLevelCoef, double minDt, double maxDt, double & dt) ; 
	void runAllCellLevelLogicsDisc(double dt);

//Ali	void runAllCellLogicsDisc_M(double dt);
	void runAllCellLogicsDisc_M(double & dt, double Damp_Coef, double InitTimeStage,
									 double timeRatio, double timeRatio_Crit_actomyo, double timeRatio_Crit_ECM, double timeRatio_Crit_Division,
									 	double volume_Increase_Target_Ratio, double volume_Increase_Scale, double postDivision_restorationRateScale, int cycle,
										 double distFromNucleus_max, double distFromNucleus_min, double distFromNucleus_normalMax1, double distFromNucleus_normalMax2,double distFromNucleus_normalMax3, 
										 double distFromNucleus_normalMax_apical1, double distFromNucleus_normalMax_apical2, double distFromNucleus_normalMax_apical3, 
										 double percentage_before_timeRatio_Crit_Division_scaling, double growthProgressSpeed, int maxApicalBasalNodeNum, double maxLengthToAddMemNodes, 
										 double mitoRndActomyoStrengthScaling, double thresholdToIntroduceNewCell, double mitoticThreshold);    //Kevin 

	void runStretchTest(double dt);

	std::vector<CVector> getAllCellCenters();
	std::vector<double> getGrowthProgressVec();

	void runAblationTest(AblationEvent &ablEvent);

	const NodeAllocPara& getAllocPara() const {
		return allocPara;
	}

	void setAllocPara(const NodeAllocPara& allocPara) {
		this->allocPara = allocPara;
	}

	AniRawData obtainAniRawData(AnimationCriteria& aniCri);
	
	std::vector<AniResumeData> obtainResumeData(); //Ali

	AniRawData obtainAniRawDataGivenCellColor(vector<double>& cellColors,
			AnimationCriteria& aniCri,vector<double>& cellsPerimeter);

	VtkAnimationData outputVtkData(AniRawData& rawAniData,
			AnimationCriteria& aniCri);


	CellsStatsData outputPolyCountData();
	SingleCellData OutputStressStrain();

	const NodeAllocPara_M& getAllocParaM() const {
		return allocPara_m;
	}

	void setAllocParaM(const NodeAllocPara_M& allocParaM) {
		allocPara_m = allocParaM;
	}

	bool aniDebug;
	EnergyCellInfo  energyCell ; 
};

#endif /* SCECELLS_H_ */
