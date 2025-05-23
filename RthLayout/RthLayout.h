// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RTHLAYOUT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RTHLAYOUT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RTHLAYOUT_EXPORTS
#define RTHLAYOUT_API __declspec(dllexport)
#else
#define RTHLAYOUT_API __declspec(dllimport)
#endif

// This class is exported from the RthLayout.dll
class RTHLAYOUT_API CRthLayout {
public:
	CRthLayout(void);
	// TODO: add your methods here.
};

extern RTHLAYOUT_API int nRthLayout;

RTHLAYOUT_API int fnRthLayout(void);
