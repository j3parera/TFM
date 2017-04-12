/*******************************************************************************
This software module was originally developed by

Agere Systems, Coding Technologies, Fraunhofer IIS, Philips

and edited by

-

in the course of development of ISO/IEC 23003 for reference purposes and its
performance may not have been optimized. This software module is an
implementation of one or more tools as specified by ISO/IEC 23003. ISO/IEC gives
You a royalty-free, worldwide, non-exclusive, copyright license to copy,
distribute, and make derivative works of this software module or modifications
thereof for use in implementations of ISO/IEC 23003 in products that satisfy
conformance criteria (if any). Those intending to use this software module in
products are advised that its use may infringe existing patents. ISO/IEC have no
liability for use of this software module or modifications thereof. Copyright is
not released for products that do not conform to audiovisual and image-coding
related ITU Recommendations and/or ISO/IEC International Standards.

Agere Systems, Coding Technologies, Fraunhofer IIS, Philips retain full right to
modify and use the code for its (their) own purpose, assign or donate the code
to a third party and to inhibit third parties from using the code for products
that do not conform to MPEG-related ITU Recommendations and/or ISO/IEC
International Standards. This copyright notice must be included in all copies or
derivative works.

Copyright (c) ISO/IEC 2009.
*******************************************************************************/




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sac_polyphase.h"
#include "sac_sbrconst.h"

#define MAX_NUM_QMF_BANDS               (128)

const double sacPolyphaseFilterbankCoefficients[10*MAX_NUM_QMF_BANDS] = {
  +0.00000000000000, -0.00027626432523, -0.00055252865047, -0.00055714895392, -0.00056176925738, -0.00052826053317, -0.00049475180896, -0.00049113730304,
  -0.00048752279712, -0.00048845096105, -0.00048937912498, -0.00049672527997, -0.00050407143497, -0.00051336393235, -0.00052265642972, -0.00053465649654,
  -0.00054665656337, -0.00055721840975, -0.00056778025613, -0.00057743665232, -0.00058709304852, -0.00060018389395, -0.00061327473938, -0.00062226204628,
  -0.00063124935319, -0.00064264134470, -0.00065403333621, -0.00066590120692, -0.00067776907764, -0.00068596527018, -0.00069416146273, -0.00070496755509,
  -0.00071577364744, -0.00072063897983, -0.00072550431222, -0.00073479924882, -0.00074409418541, -0.00074657699536, -0.00074905980532, -0.00075859849901,
  -0.00076813719270, -0.00077031102609, -0.00077248485949, -0.00077795904413, -0.00078343322877, -0.00078071008902, -0.00077798694927, -0.00077917671013,
  -0.00078036647100, -0.00078025571678, -0.00078014496257, -0.00077797134784, -0.00077579773310, -0.00076943854534, -0.00076307935757, -0.00075803974979,
  -0.00075300014201, -0.00074246792863, -0.00073193571525, -0.00072673745701, -0.00072153919876, -0.00070666647624, -0.00069179375372, -0.00067841763133,
  -0.00066504150893, -0.00064960049959, -0.00063415949025, -0.00061438569177, -0.00059461189330, -0.00057553476618, -0.00055645763906, -0.00053550743007,
  -0.00051455722108, -0.00048759488456, -0.00046063254803, -0.00043507234662, -0.00040951214522, -0.00037981486639, -0.00035011758756, -0.00031990785252,
  -0.00028969811748, -0.00024976592594, -0.00020983373440, -0.00017723591395, -0.00014463809349, -0.00010318576711, -0.00006173344072, -0.00002411923327,
  +0.00001349497418, +0.00006146664346, +0.00010943831274, +0.00015687000981, +0.00020430170688, +0.00024962740864, +0.00029495311041, +0.00034880356600,
  +0.00040265402160, +0.00045669643556, +0.00051073884952, +0.00056733823171, +0.00062393761391, +0.00068487010128, +0.00074580258865, +0.00080332346064,
  +0.00086084433262, +0.00092472158139, +0.00098859883015, +0.00105680717161, +0.00112501551307, +0.00119140198891, +0.00125778846475, +0.00132401897373,
  +0.00139024948272, +0.00146728573371, +0.00154432198471, +0.00161556515501, +0.00168680832531, +0.00176081743377, +0.00183482654224, +0.00190947030797,
  +0.00198411407369, +0.00206513621463, +0.00214615835557, +0.00222394191652, +0.00230172547746, +0.00238214358436, +0.00246256169126, +0.00254136878014,
  +0.00262017586902, +0.00270361115184, +0.00278704643465, +0.00286699560315, +0.00294694477165, +0.00302974341845, +0.00311254206525, +0.00319325170686,
  +0.00327396134847, +0.00335792438338, +0.00344188741828, +0.00352135711530, +0.00360082681231, +0.00368060955168, +0.00376039229104, +0.00384056776403,
  +0.00392074323703, +0.00400135927819, +0.00408197531935, +0.00415420112103, +0.00422642692270, +0.00429974944525, +0.00437307196781, +0.00444702862303,
  +0.00452098527825, +0.00459081566972, +0.00466064606118, +0.00472695107308, +0.00479325608498, +0.00485350822121, +0.00491376035745, +0.00497653130879,
  +0.00503930226013, +0.00509001882522, +0.00514073539032, +0.00519342600178, +0.00524611661324, +0.00529664236653, +0.00534716811982, +0.00538342285644,
  +0.00541967759307, +0.00545364080407, +0.00548760401507, +0.00551758773298, +0.00554757145088, +0.00557068687567, +0.00559380230045, +0.00560793331071,
  +0.00562206432097, +0.00563379200631, +0.00564551969164, +0.00564221982158, +0.00563891995151, +0.00563276568542, +0.00562661141932, +0.00560916214281,
  +0.00559171286630, +0.00556607463015, +0.00554043639400, +0.00550790735085, +0.00547537830770, +0.00542963794870, +0.00538389758970, +0.00532773673121,
  +0.00527157587272, +0.00520490170893, +0.00513822754514, +0.00506109816072, +0.00498396877629, +0.00489745784115, +0.00481094690600, +0.00470744996035,
  +0.00460395301471, +0.00449206959459, +0.00438018617447, +0.00425267520359, +0.00412516423270, +0.00398540252258, +0.00384564081246, +0.00369288273376,
  +0.00354012465507, +0.00337465661803, +0.00320918858098, +0.00302693218361, +0.00284467578623, +0.00264776489472, +0.00245085400321, +0.00223913581086,
  +0.00202741761850, +0.00180294293809, +0.00157846825768, +0.00133435058140, +0.00109023290512, +0.00083672966496, +0.00058322642480, +0.00030541547193,
  +0.00002760451905, -0.00025941178380, -0.00054642808664, -0.00085162081945, -0.00115681355227, -0.00148038040560, -0.00180394725893, -0.00214330981171,
  -0.00248267236449, -0.00283802510174, -0.00319337783900, -0.00356674512211, -0.00394011240522, -0.00433118601461, -0.00472225962400, -0.00512799036744,
  -0.00553372111088, -0.00595647521887, -0.00637922932685, -0.00682040550601, -0.00726158168517, -0.00772070251122, -0.00817982333726, -0.00865617814906,
  -0.00913253296085, -0.00962377725536, -0.01011502154986, -0.01062328817654, -0.01113155480321, -0.01165827719915, -0.01218499959508, -0.01272841079930,
  +0.01327182200351, +0.01383114430572, +0.01439046660792, +0.01496551097108, +0.01554055533423, +0.01613651331706, +0.01673247129989, +0.01733790471716,
  +0.01794333813443, +0.01856529063571, +0.01918724313698, +0.01982021123626, +0.02045317933555, +0.02109996718045, +0.02174675502535, +0.02240738597699,
  +0.02306801692862, +0.02374205806574, +0.02441609920285, +0.02510184197876, +0.02578758475467, +0.02648676385898, +0.02718594296329, +0.02789658016357,
  +0.02860721736385, +0.02932874155332, +0.03005026574279, +0.03077601330834, +0.03150176087389, +0.03223858448863, +0.03297540810337, +0.03371875149011,
  +0.03446209487686, +0.03521592546614, +0.03596975605542, +0.03672552054897, +0.03748128504252, +0.03824332649498, +0.03900536794745, +0.03977014250164,
  +0.04053491705584, +0.04129991325976, +0.04206490946367, +0.04283733183836, +0.04360975421304, +0.04437929738859, +0.04514884056413, +0.04591657164528,
  +0.04668430272642, +0.04745043736657, +0.04821657200672, +0.04897757378343, +0.04973857556014, +0.05049709555615, +0.05125561555216, +0.05200934510212,
  +0.05276307465207, +0.05350417574398, +0.05424527683589, +0.05498132082863, +0.05571736482138, +0.05643950491718, +0.05716164501299, +0.05787660668779,
  +0.05859156836260, +0.05928765819011, +0.05998374801761, +0.06066463259484, +0.06134551717207, +0.06201564899189, +0.06268578081172, +0.06332868530926,
  +0.06397158980681, +0.06459815022531, +0.06522471064380, +0.06583073093242, +0.06643675122104, +0.06702217486666, +0.06760759851228, +0.06815599067370,
  +0.06870438283512, +0.06923370365320, +0.06976302447127, +0.07026294777196, +0.07076287107266, +0.07123156919184, +0.07170026731102, +0.07213426282092,
  +0.07256825833083, +0.07296514191943, +0.07336202550803, +0.07373119487572, +0.07410036424342, +0.07442281002768, +0.07474525581194, +0.07502949471607,
  +0.07531373362019, +0.07555728474301, +0.07580083586584, +0.07600004189990, +0.07619924793396, +0.07634923248757, +0.07649921704119, +0.07660428304182,
  +0.07670934904245, +0.07676337330604, +0.07681739756964, +0.07682019935444, +0.07682300113923, +0.07677174677835, +0.07672049241746, +0.07661278212470,
  +0.07650507183194, +0.07633995200865, +0.07617483218536, +0.07595270391799, +0.07573057565061, +0.07544410058966, +0.07515762552870, +0.07481203250217,
  +0.07446643947564, +0.07405352002592, +0.07364060057620, +0.07315903242460, +0.07267746427299, +0.07213005037601, +0.07158263647903, +0.07096797191498,
  +0.07035330735093, +0.06965985433522, +0.06896640131951, +0.06820945173559, +0.06745250215166, +0.06661078450837, +0.06576906686508, +0.06485677373071,
  +0.06394448059633, +0.06295237925010, +0.06196027790387, +0.06088846749238, +0.05981665708090, +0.05866596313978, +0.05751526919867, +0.05628063631438,
  +0.05504600343009, +0.05372769280188, +0.05240938217366, +0.05100362490406, +0.04959786763445, +0.04811409907573, +0.04663033051701, +0.04505360436830,
  +0.04347687821958, +0.04181135303042, +0.04014582784127, +0.03839381976130, +0.03664181168133, +0.03480010237412, +0.03295839306691, +0.03102039683408,
  +0.02908240060125, +0.02705657839517, +0.02503075618909, +0.02291523173766, +0.02079970728622, +0.01858491655425, +0.01637012582228, +0.01406625455043,
  +0.01176238327857, +0.00936303474737, +0.00696368621617, +0.00447012318060, +0.00197656014503, -0.00061606476900, -0.00320868968304, -0.00588993229835,
  -0.00857117491366, -0.01135002882462, -0.01412888273558, -0.01700614783065, -0.01988341292573, -0.02285307090319, -0.02582272888064, -0.02888792816698,
  -0.03195312745332, -0.03511539233077, -0.03827765720822, -0.04152916968339, -0.04478068215856, -0.04813054991895, -0.05148041767934, -0.05492547518135,
  -0.05837053268336, -0.06190575899848, -0.06544098531359, -0.06906765769744, -0.07269433008129, -0.07641581176204, -0.08013729344279, -0.08394602354936,
  -0.08775475365593, -0.09165404447254, -0.09555333528914, -0.09954314420189, -0.10353295311463, -0.10760782314597, -0.11168269317730, -0.11584524582265,
  -0.12000779846800, -0.12425404175339, -0.12850028503878, -0.13282773057906, -0.13715517611934, -0.14156591261902, -0.14597664911870, -0.15046867811238,
  -0.15496070710605, -0.15952829633637, -0.16409588556669, -0.16873835139187, -0.17338081721706, -0.17809903603424, -0.18281725485142, -0.18760696471205,
  -0.19239667457267, -0.19726084612685, -0.20212501768103, -0.20704930153079, -0.21197358538056, -0.21696942751102, -0.22196526964149, -0.22701717835470,
  -0.23206908706791, -0.23718538776383, -0.24230168845974, -0.24747485970848, -0.25264803095722, -0.25787668045162, -0.26310532994603, -0.26838436700114,
  -0.27366340405625, -0.27899241148355, -0.28432141891085, -0.28969654530865, -0.29507167170646, -0.30049076461281, -0.30590985751916, -0.31136887444186,
  -0.31682789136456, -0.32231963204281, -0.32781137272105, -0.33334182105385, -0.33887226938665, -0.34443184083987, -0.34999141229310, -0.35557520130332,
  +0.36115899031355, +0.36676927247208, +0.37237955463061, +0.37800727801052, +0.38363500139043, +0.38927808877359, +0.39492117615675, +0.40057647191650,
  +0.40623176767625, +0.41190072868017, +0.41756968968409, +0.42324084087891, +0.42891199207373, +0.43458368375519, +0.44025537543665, +0.44592751450245,
  +0.45159965356824, +0.45726523104791, +0.46293080852757, +0.46858806499436, +0.47424532146115, +0.47988531528607, +0.48552530911099, +0.49114806728403,
  +0.49677082545707, +0.50237628773070, +0.50798175000434, +0.51355262351413, +0.51912349702391, +0.52467379329623, +0.53022408956855, +0.53573971722089,
  +0.54125534487322, +0.54673023536192, +0.55220512585061, +0.55764201993216, +0.56307891401370, +0.56846566359147, +0.57385241316923, +0.57919636835801,
  +0.58454032354679, +0.58982631608587, +0.59511230862496, +0.60034533125838, +0.60557835389180, +0.61074467354735, +0.61591099320291, +0.62101763138173,
  +0.62612426956055, +0.63116114016670, +0.63619801077286, +0.64116249018373, +0.64612696959461, +0.65101429992066, +0.65590163024671, +0.66070780913149,
  +0.66551398801627, +0.67024015351670, +0.67496631901712, +0.67960082418155, +0.68423532934598, +0.68878178350815, +0.69332823767032, +0.69778355480286,
  +0.70223887193539, +0.70658995728317, +0.71094104263095, +0.71519365306328, +0.71944626349561, +0.72359557676278, +0.72774489002994, +0.73178303292882,
  +0.73582117582769, +0.73975198109629, +0.74368278636488, +0.74749826598863, +0.75131374561237, +0.75501091084740, +0.75870807608242, +0.76228778129591,
  +0.76586748650939, +0.76932278732133, +0.77277808813327, +0.77610342001772, +0.77942875190216, +0.78263203197068, +0.78583531203920, +0.78890444810172,
  +0.79197358416424, +0.79491011277062, +0.79784664137700, +0.80064760828102, +0.80344857518505, +0.80610903781498, +0.80876950044491, +0.81129431375354,
  +0.81381912706217, +0.81619836376342, +0.81857760046468, +0.82080979475938, +0.82304198905409, +0.82513476189384, +0.82722753473360, +0.82916569022440,
  +0.83110384571520, +0.83289879094961, +0.83469373618402, +0.83633273498633, +0.83797173378865, +0.83946293651793, +0.84095413924722, +0.84228898368363,
  +0.84362382812005, +0.84480283755106, +0.84598184698206, +0.84700671234485, +0.84803157770763, +0.84890604877515, +0.84978051984268, +0.85048883616805,
  +0.85119715249343, +0.85175092800745, +0.85230470352147, +0.85270339924582, +0.85310209497017, +0.85333707618062, +0.85357205739107, +0.85365530872522,
  +0.85373856005937, +0.85365530872522, +0.85357205739107, +0.85333707618062, +0.85310209497017, +0.85270339924582, +0.85230470352147, +0.85175092800745,
  +0.85119715249343, +0.85048883616805, +0.84978051984268, +0.84890604877515, +0.84803157770763, +0.84700671234485, +0.84598184698206, +0.84480283755106,
  +0.84362382812005, +0.84228898368363, +0.84095413924722, +0.83946293651793, +0.83797173378865, +0.83633273498633, +0.83469373618402, +0.83289879094961,
  +0.83110384571520, +0.82916569022440, +0.82722753473360, +0.82513476189384, +0.82304198905409, +0.82080979475938, +0.81857760046468, +0.81619836376342,
  +0.81381912706217, +0.81129431375354, +0.80876950044491, +0.80610903781498, +0.80344857518505, +0.80064760828102, +0.79784664137700, +0.79491011277062,
  +0.79197358416424, +0.78890444810172, +0.78583531203920, +0.78263203197068, +0.77942875190216, +0.77610342001772, +0.77277808813327, +0.76932278732133,
  +0.76586748650939, +0.76228778129591, +0.75870807608242, +0.75501091084740, +0.75131374561237, +0.74749826598863, +0.74368278636488, +0.73975198109629,
  +0.73582117582769, +0.73178303292882, +0.72774489002994, +0.72359557676278, +0.71944626349561, +0.71519365306328, +0.71094104263095, +0.70658995728317,
  +0.70223887193539, +0.69778355480286, +0.69332823767032, +0.68878178350815, +0.68423532934598, +0.67960082418155, +0.67496631901712, +0.67024015351670,
  +0.66551398801627, +0.66070780913149, +0.65590163024671, +0.65101429992066, +0.64612696959461, +0.64116249018373, +0.63619801077286, +0.63116114016670,
  +0.62612426956055, +0.62101763138173, +0.61591099320291, +0.61074467354735, +0.60557835389180, +0.60034533125838, +0.59511230862496, +0.58982631608587,
  +0.58454032354679, +0.57919636835801, +0.57385241316923, +0.56846566359147, +0.56307891401370, +0.55764201993216, +0.55220512585061, +0.54673023536192,
  +0.54125534487322, +0.53573971722089, +0.53022408956855, +0.52467379329623, +0.51912349702391, +0.51355262351413, +0.50798175000434, +0.50237628773070,
  +0.49677082545707, +0.49114806728403, +0.48552530911099, +0.47988531528607, +0.47424532146115, +0.46858806499436, +0.46293080852757, +0.45726523104791,
  +0.45159965356824, +0.44592751450245, +0.44025537543665, +0.43458368375519, +0.42891199207373, +0.42324084087891, +0.41756968968409, +0.41190072868017,
  +0.40623176767625, +0.40057647191650, +0.39492117615675, +0.38927808877359, +0.38363500139043, +0.37800727801052, +0.37237955463061, +0.36676927247208,
  -0.36115899031355, -0.35557520130332, -0.34999141229310, -0.34443184083987, -0.33887226938665, -0.33334182105385, -0.32781137272105, -0.32231963204281,
  -0.31682789136456, -0.31136887444186, -0.30590985751916, -0.30049076461281, -0.29507167170646, -0.28969654530865, -0.28432141891085, -0.27899241148355,
  -0.27366340405625, -0.26838436700114, -0.26310532994603, -0.25787668045162, -0.25264803095722, -0.24747485970848, -0.24230168845974, -0.23718538776383,
  -0.23206908706791, -0.22701717835470, -0.22196526964149, -0.21696942751102, -0.21197358538056, -0.20704930153079, -0.20212501768103, -0.19726084612685,
  -0.19239667457267, -0.18760696471205, -0.18281725485142, -0.17809903603424, -0.17338081721706, -0.16873835139187, -0.16409588556669, -0.15952829633637,
  -0.15496070710605, -0.15046867811238, -0.14597664911870, -0.14156591261902, -0.13715517611934, -0.13282773057906, -0.12850028503878, -0.12425404175339,
  -0.12000779846800, -0.11584524582265, -0.11168269317730, -0.10760782314597, -0.10353295311463, -0.09954314420189, -0.09555333528914, -0.09165404447254,
  -0.08775475365593, -0.08394602354936, -0.08013729344279, -0.07641581176204, -0.07269433008129, -0.06906765769744, -0.06544098531359, -0.06190575899848,
  -0.05837053268336, -0.05492547518135, -0.05148041767934, -0.04813054991895, -0.04478068215856, -0.04152916968339, -0.03827765720822, -0.03511539233077,
  -0.03195312745332, -0.02888792816698, -0.02582272888064, -0.02285307090319, -0.01988341292573, -0.01700614783065, -0.01412888273558, -0.01135002882462,
  -0.00857117491366, -0.00588993229835, -0.00320868968304, -0.00061606476900, +0.00197656014503, +0.00447012318060, +0.00696368621617, +0.00936303474737,
  +0.01176238327857, +0.01406625455043, +0.01637012582228, +0.01858491655425, +0.02079970728622, +0.02291523173766, +0.02503075618909, +0.02705657839517,
  +0.02908240060125, +0.03102039683408, +0.03295839306691, +0.03480010237412, +0.03664181168133, +0.03839381976130, +0.04014582784127, +0.04181135303042,
  +0.04347687821958, +0.04505360436830, +0.04663033051701, +0.04811409907573, +0.04959786763445, +0.05100362490406, +0.05240938217366, +0.05372769280188,
  +0.05504600343009, +0.05628063631438, +0.05751526919867, +0.05866596313978, +0.05981665708090, +0.06088846749238, +0.06196027790387, +0.06295237925010,
  +0.06394448059633, +0.06485677373071, +0.06576906686508, +0.06661078450837, +0.06745250215166, +0.06820945173559, +0.06896640131951, +0.06965985433522,
  +0.07035330735093, +0.07096797191498, +0.07158263647903, +0.07213005037601, +0.07267746427299, +0.07315903242460, +0.07364060057620, +0.07405352002592,
  +0.07446643947564, +0.07481203250217, +0.07515762552870, +0.07544410058966, +0.07573057565061, +0.07595270391799, +0.07617483218536, +0.07633995200865,
  +0.07650507183194, +0.07661278212470, +0.07672049241746, +0.07677174677835, +0.07682300113923, +0.07682019935444, +0.07681739756964, +0.07676337330604,
  +0.07670934904245, +0.07660428304182, +0.07649921704119, +0.07634923248757, +0.07619924793396, +0.07600004189990, +0.07580083586584, +0.07555728474301,
  +0.07531373362019, +0.07502949471607, +0.07474525581194, +0.07442281002768, +0.07410036424342, +0.07373119487572, +0.07336202550803, +0.07296514191943,
  +0.07256825833083, +0.07213426282092, +0.07170026731102, +0.07123156919184, +0.07076287107266, +0.07026294777196, +0.06976302447127, +0.06923370365320,
  +0.06870438283512, +0.06815599067370, +0.06760759851228, +0.06702217486666, +0.06643675122104, +0.06583073093242, +0.06522471064380, +0.06459815022531,
  +0.06397158980681, +0.06332868530926, +0.06268578081172, +0.06201564899189, +0.06134551717207, +0.06066463259484, +0.05998374801761, +0.05928765819011,
  +0.05859156836260, +0.05787660668779, +0.05716164501299, +0.05643950491718, +0.05571736482138, +0.05498132082863, +0.05424527683589, +0.05350417574398,
  +0.05276307465207, +0.05200934510212, +0.05125561555216, +0.05049709555615, +0.04973857556014, +0.04897757378343, +0.04821657200672, +0.04745043736657,
  +0.04668430272642, +0.04591657164528, +0.04514884056413, +0.04437929738859, +0.04360975421304, +0.04283733183836, +0.04206490946367, +0.04129991325976,
  +0.04053491705584, +0.03977014250164, +0.03900536794745, +0.03824332649498, +0.03748128504252, +0.03672552054897, +0.03596975605542, +0.03521592546614,
  +0.03446209487686, +0.03371875149011, +0.03297540810337, +0.03223858448863, +0.03150176087389, +0.03077601330834, +0.03005026574279, +0.02932874155332,
  +0.02860721736385, +0.02789658016357, +0.02718594296329, +0.02648676385898, +0.02578758475467, +0.02510184197876, +0.02441609920285, +0.02374205806574,
  +0.02306801692862, +0.02240738597699, +0.02174675502535, +0.02109996718045, +0.02045317933555, +0.01982021123626, +0.01918724313698, +0.01856529063571,
  +0.01794333813443, +0.01733790471716, +0.01673247129989, +0.01613651331706, +0.01554055533423, +0.01496551097108, +0.01439046660792, +0.01383114430572,
  -0.01327182200351, -0.01272841079930, -0.01218499959508, -0.01165827719915, -0.01113155480321, -0.01062328817654, -0.01011502154986, -0.00962377725536,
  -0.00913253296085, -0.00865617814906, -0.00817982333726, -0.00772070251122, -0.00726158168517, -0.00682040550601, -0.00637922932685, -0.00595647521887,
  -0.00553372111088, -0.00512799036744, -0.00472225962400, -0.00433118601461, -0.00394011240522, -0.00356674512211, -0.00319337783900, -0.00283802510174,
  -0.00248267236449, -0.00214330981171, -0.00180394725893, -0.00148038040560, -0.00115681355227, -0.00085162081945, -0.00054642808664, -0.00025941178380,
  +0.00002760451905, +0.00030541547193, +0.00058322642480, +0.00083672966496, +0.00109023290512, +0.00133435058140, +0.00157846825768, +0.00180294293809,
  +0.00202741761850, +0.00223913581086, +0.00245085400321, +0.00264776489472, +0.00284467578623, +0.00302693218361, +0.00320918858098, +0.00337465661803,
  +0.00354012465507, +0.00369288273376, +0.00384564081246, +0.00398540252258, +0.00412516423270, +0.00425267520359, +0.00438018617447, +0.00449206959459,
  +0.00460395301471, +0.00470744996035, +0.00481094690600, +0.00489745784115, +0.00498396877629, +0.00506109816072, +0.00513822754514, +0.00520490170893,
  +0.00527157587272, +0.00532773673121, +0.00538389758970, +0.00542963794870, +0.00547537830770, +0.00550790735085, +0.00554043639400, +0.00556607463015,
  +0.00559171286630, +0.00560916214281, +0.00562661141932, +0.00563276568542, +0.00563891995151, +0.00564221982158, +0.00564551969164, +0.00563379200631,
  +0.00562206432097, +0.00560793331071, +0.00559380230045, +0.00557068687567, +0.00554757145088, +0.00551758773298, +0.00548760401507, +0.00545364080407,
  +0.00541967759307, +0.00538342285644, +0.00534716811982, +0.00529664236653, +0.00524611661324, +0.00519342600178, +0.00514073539032, +0.00509001882522,
  +0.00503930226013, +0.00497653130879, +0.00491376035745, +0.00485350822121, +0.00479325608498, +0.00472695107308, +0.00466064606118, +0.00459081566972,
  +0.00452098527825, +0.00444702862303, +0.00437307196781, +0.00429974944525, +0.00422642692270, +0.00415420112103, +0.00408197531935, +0.00400135927819,
  +0.00392074323703, +0.00384056776403, +0.00376039229104, +0.00368060955168, +0.00360082681231, +0.00352135711530, +0.00344188741828, +0.00335792438338,
  +0.00327396134847, +0.00319325170686, +0.00311254206525, +0.00302974341845, +0.00294694477165, +0.00286699560315, +0.00278704643465, +0.00270361115184,
  +0.00262017586902, +0.00254136878014, +0.00246256169126, +0.00238214358436, +0.00230172547746, +0.00222394191652, +0.00214615835557, +0.00206513621463,
  +0.00198411407369, +0.00190947030797, +0.00183482654224, +0.00176081743377, +0.00168680832531, +0.00161556515501, +0.00154432198471, +0.00146728573371,
  +0.00139024948272, +0.00132401897373, +0.00125778846475, +0.00119140198891, +0.00112501551307, +0.00105680717161, +0.00098859883015, +0.00092472158139,
  +0.00086084433262, +0.00080332346064, +0.00074580258865, +0.00068487010128, +0.00062393761391, +0.00056733823171, +0.00051073884952, +0.00045669643556,
  +0.00040265402160, +0.00034880356600, +0.00029495311041, +0.00024962740864, +0.00020430170688, +0.00015687000981, +0.00010943831274, +0.00006146664346,
  +0.00001349497418, -0.00002411923327, -0.00006173344072, -0.00010318576711, -0.00014463809349, -0.00017723591395, -0.00020983373440, -0.00024976592594,
  -0.00028969811748, -0.00031990785252, -0.00035011758756, -0.00037981486639, -0.00040951214522, -0.00043507234662, -0.00046063254803, -0.00048759488456,
  -0.00051455722108, -0.00053550743007, -0.00055645763906, -0.00057553476618, -0.00059461189330, -0.00061438569177, -0.00063415949025, -0.00064960049959,
  -0.00066504150893, -0.00067841763133, -0.00069179375372, -0.00070666647624, -0.00072153919876, -0.00072673745701, -0.00073193571525, -0.00074246792863,
  -0.00075300014201, -0.00075803974979, -0.00076307935757, -0.00076943854534, -0.00077579773310, -0.00077797134784, -0.00078014496257, -0.00078025571678,
  -0.00078036647100, -0.00077917671013, -0.00077798694927, -0.00078071008902, -0.00078343322877, -0.00077795904413, -0.00077248485949, -0.00077031102609,
  -0.00076813719270, -0.00075859849901, -0.00074905980532, -0.00074657699536, -0.00074409418541, -0.00073479924882, -0.00072550431222, -0.00072063897983,
  -0.00071577364744, -0.00070496755509, -0.00069416146273, -0.00068596527018, -0.00067776907764, -0.00066590120692, -0.00065403333621, -0.00064264134470,
  -0.00063124935319, -0.00062226204628, -0.00061327473938, -0.00060018389395, -0.00058709304852, -0.00057743665232, -0.00056778025613, -0.00055721840975,
  -0.00054665656337, -0.00053465649654, -0.00052265642972, -0.00051336393235, -0.00050407143497, -0.00049672527997, -0.00048937912498, -0.00048845096105,
  -0.00048752279712, -0.00049113730304, -0.00049475180896, -0.00052826053317, -0.00056176925738, -0.00055714895392, -0.00055252865047, -0.00027626432523
};


struct SAC_POLYPHASE_ANA_FILTERBANK
{
  double *X; 
};

struct SAC_POLYPHASE_SYN_FILTERBANK
{
  double *V; 
};

static struct M
{
  int resolution;
  double real[MAX_NUM_QMF_BANDS][2*MAX_NUM_QMF_BANDS];
  double imag[MAX_NUM_QMF_BANDS][2*MAX_NUM_QMF_BANDS];

} M;  

static struct N
{
  int resolution;
  double real[2*MAX_NUM_QMF_BANDS][MAX_NUM_QMF_BANDS];
  double imag[2*MAX_NUM_QMF_BANDS][MAX_NUM_QMF_BANDS];

} N;  


void
SacDecInitSynFilterbank(const Twiddle *twiddle,
                     int resolution)
{
  int l,k;
  double gain;

  N.resolution = resolution;

#ifdef PARTIALLY_COMPLEX

  gain = sqrt(2.0) / 64.0;

  for ( l=0; l<2*resolution; l++ ) {
    for ( k=0; k<resolution; k++ ) {
      N.real[l][k] = gain * cos((PI/2/resolution) * (k+0.5) * (2*l-resolution));
    }
  }

#else
  
  gain = 1.0 / 64.0;
 
  if (twiddle != NULL) {
    for ( l=0; l<2*resolution; l++ ) {
      for ( k=0; k<resolution; k++ ) {
        N.real[l][k] = gain * cos((PI/resolution) * ((k+0.5) * (l+twiddle->fi) + twiddle->beta ));
        N.imag[l][k] = gain * sin((PI/resolution) * ((k+0.5) * (l+twiddle->fi) + twiddle->beta ));
      }
    }
  }
  else {
    for ( l=0; l<2*resolution; l++ ) {
      for ( k=0; k<resolution; k++ ) {
        N.real[l][k] = gain * cos((PI/2/resolution) * (k+0.5) * (2*l-255*resolution/64.0));
        N.imag[l][k] = gain * sin((PI/2/resolution) * (k+0.5) * (2*l-255*resolution/64.0));
      }
    }
  }
#endif
}


void
SacDecOpenSynFilterbank(SAC_POLYPHASE_SYN_FILTERBANK **selfPtr)
{
  SAC_POLYPHASE_SYN_FILTERBANK *self;

  self = calloc(1, sizeof(SAC_POLYPHASE_SYN_FILTERBANK));
  if (self != NULL) {
    self->V = calloc(20 * N.resolution, sizeof(double));
  }
  *selfPtr = self;
}


void
SacDecCloseSynFilterbank(SAC_POLYPHASE_SYN_FILTERBANK *self)
{
  if (self != NULL) {
    free(self->V);
  }
  free(self);
}


void
SacDecCalculateSynFilterbank(SAC_POLYPHASE_SYN_FILTERBANK *self,
                          float  *Sr,
                          float  *Si,
                          double *timeSig)
{
  int i,j,k,l;
  double   U[10 * MAX_NUM_QMF_BANDS];
  double   W[10 * MAX_NUM_QMF_BANDS];
  double  *V = self->V;
  double   realAccu;
  const double* C = sacPolyphaseFilterbankCoefficients;
  int resolution = N.resolution;

  
  for ( l=20*resolution-1; l>=2*resolution; l-- ) {
    V[l] = V[l-2*resolution];
  }

  
  for ( l=0; l<2*resolution; l++ ) {
    realAccu = 0.0;
    for ( k=0; k<resolution; k++ ) {
      realAccu = realAccu 
#ifdef PARTIALLY_COMPLEX
      + Sr[k] * N.real[l][k]; 
#else
      + Sr[k] * N.real[l][k] 
      - Si[k] * N.imag[l][k];
#endif
    }
    V[l] = realAccu;
  }

  
  for ( i=0; i<5; i++ ) {
    for ( j=0; j<resolution; j++ ) {
      U[2*resolution*i+j]            = V[4*resolution*i+j];
      U[2*resolution*i+resolution+j] = V[4*resolution*i+3*resolution+j];
    }
  }

  
  for ( k=0; k<10*resolution; k++ ) {
    W[k] = U[k] * C[k*MAX_NUM_QMF_BANDS/resolution];
  }

  
  for ( i=0; i<resolution; i++ ) {
    realAccu = 0.0;
    for ( j=0; j<10; j++ ) {
      realAccu = realAccu + W[resolution*j+i];
    }
    timeSig[i] = (float) realAccu;
  }
}


void
SacDecInitAnaFilterbank(const Twiddle *twiddle,
                     int resolution)
{
  int k,l;
  double gain;

  M.resolution = resolution;

#ifdef PARTIALLY_COMPLEX
  
  gain = sqrt(2.0) * 64.0 / resolution;
  
  for ( k=0; k<resolution; k++ ) {
    for ( l=0; l<2*resolution; l++ ) {
      M.real[k][l] = gain * cos((PI/2/resolution) * (k+0.5) * (2*l-3*resolution));
    }
  }

#else

  gain = 64.0 / resolution;
  
  if (twiddle != NULL) {
    for ( k=0; k<resolution; k++ ) {
      for ( l=0; l<2*resolution; l++ ) {
        M.real[k][l] = gain * cos((PI/resolution) * ((k+0.5) * (l-10*resolution-twiddle->fi) - twiddle->beta));
        M.imag[k][l] = gain * sin((PI/resolution) * ((k+0.5) * (l-10*resolution-twiddle->fi) - twiddle->beta));
      }
    }
  }
  else {
    for ( k=0; k<resolution; k++ ) {
      for ( l=0; l<2*resolution; l++ ) {
        M.real[k][l] = gain * cos((PI/2/resolution) * (k+0.5) * (2*l-resolution/64.0));
        M.imag[k][l] = gain * sin((PI/2/resolution) * (k+0.5) * (2*l-resolution/64.0));
      }
    }
  }
  
#endif  
}


void
SacDecOpenAnaFilterbank(SAC_POLYPHASE_ANA_FILTERBANK **selfPtr)
{
  SAC_POLYPHASE_ANA_FILTERBANK *self;

  self = calloc(1, sizeof(SAC_POLYPHASE_ANA_FILTERBANK));
  if (self != NULL) {
    self->X = calloc(10 * M.resolution, sizeof(double));
  }
  *selfPtr = self;
}


void
SacDecCloseAnaFilterbank(SAC_POLYPHASE_ANA_FILTERBANK *self)
{
  if (self != NULL) {
    free(self->X);
  }
  free(self);
}


void
SacDecCalculateAnaFilterbank(SAC_POLYPHASE_ANA_FILTERBANK *self,
                          float * timeSig,
                          float * Sr,
                          float * Si)
{
  int i,j,k,l;
  float   Z[10 * MAX_NUM_QMF_BANDS];
  float   Y[2 * MAX_NUM_QMF_BANDS];
  double *X = self->X;
  const double* C = sacPolyphaseFilterbankCoefficients;
  int resolution = M.resolution;

  
  for ( i=10*resolution-1; i>=resolution; i-- ) {
    X[i] = X[i-resolution];
  }

  
  for ( i=resolution-1; i>=0; i-- ) {
    X[i] = timeSig[resolution-1-i];
  }

  
  for ( i=0; i<10*resolution; i++ ) {
    Z[i] = (float) (X[i] * C[i*MAX_NUM_QMF_BANDS/resolution]);
  }

  
  for ( i=0; i<2*resolution; i++ ) {
    Y[i] = 0.0f;
    for ( j=0; j<5; j++ ) {
      Y[i] += Z[i + j * 2 * resolution];
    }
  }
#ifdef PARTIALLY_COMPLEX
  
  for ( k=0; k<resolution; k++ ) {
    Sr[k] = 0.0f;
    for ( l=0; l<2*resolution; l++ ) {
      Sr[k] += (float) (Y[l] * M.real[k][l]);
    }
  }
#else
  
  for ( k=0; k<resolution; k++ ) {
    Sr[k] = 0.0f;
    Si[k] = 0.0f;
    for ( l=0; l<2*resolution; l++ ) {
      Sr[k] += (float) (Y[l] * M.real[k][l]);
      Si[k] += (float) (Y[l] * M.imag[k][l]);
    }
  }
#endif
}

void
SacDecGetFilterbankPrototype(int resolution,
                          float * prototype)
{
  const double* C = sacPolyphaseFilterbankCoefficients;
  int i;

  for ( i=0; i<10*resolution; i++ ) {
    prototype[i] = (float) C[i*MAX_NUM_QMF_BANDS/resolution];
  }

  for ( i=2*resolution; i<4*resolution; i++ ) {
    prototype[i] = -prototype[i];
  }

  for ( i=6*resolution; i<8*resolution; i++ ) {
    prototype[i] = -prototype[i];
  }
}
