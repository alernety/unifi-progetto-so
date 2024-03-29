#ifndef SRC_RAILWAY_MANAGER_DEFAULT_VALUES_H_
#define SRC_RAILWAY_MANAGER_DEFAULT_VALUES_H_

#define RAILWAY_DEFAULT_STRING                                                       \
	"S1<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA1\n"    \
	"MA1<platform_data>1<platform_data>0<platform_data>1<platform_data>S1,MA2\n" \
	"MA2<platform_data>1<platform_data>0<platform_data>1<platform_data>MA1,"     \
	"MA3\n"                                                                      \
	"MA3<platform_data>1<platform_data>0<platform_data>1<platform_data>MA2,MA4," \
	"MA7,MA8\n"                                                                  \
	"MA4<platform_data>1<platform_data>0<platform_data>1<platform_data>MA3,S5\n" \
	"S5<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA4\n"    \
	"S2<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA5\n"    \
	"MA5<platform_data>1<platform_data>0<platform_data>1<platform_data>S2,MA6\n" \
	"MA6<platform_data>1<platform_data>0<platform_data>1<platform_data>MA5,"     \
	"MA7\n"                                                                      \
	"MA7<platform_data>1<platform_data>0<platform_data>1<platform_data>MA6,"     \
	"MA3\n"                                                                      \
	"MA8<platform_data>1<platform_data>0<platform_data>1<platform_data>MA3,S6\n" \
	"S6<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA8\n"    \
	"S3<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA9\n"    \
	"MA9<platform_data>1<platform_data>0<platform_data>1<platform_data>S3,"      \
	"MA10\n"                                                                     \
	"MA10<platform_data>1<platform_data>0<platform_data>1<platform_data>MA9,"    \
	"MA11\n"                                                                     \
	"MA11<platform_data>1<platform_data>0<platform_data>1<platform_data>MA10,"   \
	"MA12\n"                                                                     \
	"MA12<platform_data>1<platform_data>0<platform_data>1<platform_data>MA11,"   \
	"MA13,MA16,S8\n"                                                             \
	"MA13<platform_data>1<platform_data>0<platform_data>1<platform_data>MA12,"   \
	"S7\n"                                                                       \
	"S7<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA13\n"   \
	"S4<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA14\n"   \
	"MA14<platform_data>1<platform_data>0<platform_data>1<platform_data>S4,"     \
	"MA15\n"                                                                     \
	"MA15<platform_data>1<platform_data>0<platform_data>1<platform_data>MA14,"   \
	"MA16\n"                                                                     \
	"MA16<platform_data>1<platform_data>0<platform_data>1<platform_data>MA15,"   \
	"MA12\n"                                                                     \
	"S8<platform_data>0<platform_data>0<platform_data>-1<platform_data>MA12"

#define MAPPA1_DEFAULT_STRING                   \
	"S1, MA1, MA2, MA3, MA8, S6\n"          \
	"S2, MA5, MA6, MA7, MA3, MA8, S6\n"     \
	"S7, MA13, MA12, MA11, MA10, MA9, S3\n" \
	"S4, MA14, MA15, MA16, MA12, S8"
#define MAPPA2_DEFAULT_STRING               \
	"S2, MA5, MA6, MA7, MA3, MA8, S6\n" \
	"S3, MA9, MA10, MA11, MA12, S8\n"   \
	"S4, MA14, MA15, MA16, MA12, S8\n"  \
	"S6, MA8, MA3, MA2, MA1, S1\n"      \
	"S5, MA4, MA3, MA2, MA1, S1"

#endif // SRC_RAILWAY_MANAGER_DEFAULT_VALUES_H_
