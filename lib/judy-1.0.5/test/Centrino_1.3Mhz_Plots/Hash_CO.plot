# StringCompare -n14962357 -A Hash -H1048576 -P40 -L10 -C -M100000 /home/data/domnames.txt
# This file is in a format to input to 'jbgraph'
# XLABEL Stored
# YLABEL Microseconds / Index
# COLHEAD 1 Total Insert attempts
# COLHEAD 2 Number Gets
# COLHEAD 3 Duplicate strings
# COLHEAD 4 Insert Time (uS)
# COLHEAD 5 Get Time (uS)
# COLHEAD 6 Hash Chain Length
# COLHEAD 7 Average RAM/String
# Linux localhost 2.6.3-4mdkenterprise #1 SMP Tue Mar 2 07:00:53 CET 2004 i686
# 32 Bit CPU
# Processor speed compiled at 1299 Mhz
# Hash record struct: sizeof(hrec_t) = 16
# Allocate Hash table = 1048576 elements
# 11218731 (75.0%) non-Word_t aligned string buffers
# Ram used for input data = 372621771 bytes
# Average string length = 15.9 bytes
# 3200000 bytes malloc() for 'cached' strings for Get measurement
# Access Time    =  0.103 uS average per string (mostly from Cache)
# HashStr() Time =  0.270 uS average per string (mostly from Cache)
# Access Time    =  0.287 uS average per string (mostly from RAM)
# HashStr() Time =  0.477 uS average per string (mostly from RAM)
# Pass 0
# TotInserts  DeltaGets  DupStrs InsTime GetTime HChainLen Ram/String
#          1          1        0 5775.911   1.182  1.000000     4194356.0
#          2          2        0   3.406   0.417  1.000000     2097190.0
#          3          3        0   1.251   0.374  1.000000     1398136.0
#          4          4        0   1.465   0.380  1.000000     1048610.0
#          5          5        0   1.154   0.363  1.000000      838893.6
#          6          6        0   0.996   0.347  1.000000      699082.0
#          7          7        0   1.109   0.356  1.000000      599217.7
#          8          8        0   1.564   0.347  1.000000      524318.5
#          9          9        0   1.189   0.355  1.000000      466064.4
#         10         10        0   1.176   0.352  1.000000      419460.8
#         11         11        0   1.268   0.359  1.000000      381330.9
#         12         12        0   1.264   0.364  1.000000      349556.0
#         13         13        0   1.357   0.363  1.000000      322669.2
#         14         14        0   1.467   0.364  1.000000      299623.7
#         15         15        0   1.070   0.366  1.000000      279650.9
#         16         16        0   1.404   0.375  1.000000      262175.0
#         17         17        0   1.544   0.367  1.000000      246754.4
#         18         18        0   0.851   0.364  1.000000      233047.1
#         19         19        0   1.139   0.366  1.000000      220783.2
#         20         20        0   1.238   0.366  1.000000      209745.4
#         21         21        0   1.195   0.363  1.000000      199758.9
#         22         22        0   1.176   0.365  1.000000      190680.4
#         23         23        0  13.957   0.366  1.000000      182391.1
#         24         24        0   1.159   0.361  1.000000      174792.5
#         25         25        0   1.288   0.356  1.000000      167801.8
#         26         26        0   1.179   0.357  1.000000      161348.9
#         27         27        0   1.204   0.361  1.000000      155374.4
#         28         28        0   1.125   0.359  1.000000      149826.1
#         29         29        0   1.052   0.359  1.000000      144660.8
#         30         30        0   2.443   0.368  1.000000      139839.6
#         31         31        0   1.527   0.368  1.000000      135330.2
#         32         32        0   1.390   0.365  1.000000      131102.0
#         34         34        0   1.179   0.365  1.000000      123391.6
#         36         36        0   1.034   0.366  1.000000      116538.3
#         38         38        0   1.010   0.368  1.000000      110406.4
#         40         40        0   1.142   0.367  1.000000      104887.5
#         42         42        0   0.941   0.366  1.000000       99894.2
#         44         44        0   1.292   0.368  1.000000       95355.0
#         46         46        0   1.072   0.369  1.000000       91210.5
#         48         48        0   0.946   0.365  1.000000       87411.2
#         50         50        0   1.057   0.375  1.000000       83916.0
#         53         53        0   1.134   0.368  1.000000       79168.0
#         56         56        0   1.022   0.367  1.000000       74928.4
#         59         59        0   0.736   0.364  1.000000       71119.7
#         62         62        0   1.059   0.364  1.000000       67680.0
#         65         65        0   1.049   0.364  1.000000       64557.7
#         69         69        0   1.011   0.365  1.000000       60816.9
#         73         73        0   0.864   0.359  1.000000       57485.9
#         77         77        0   0.998   0.359  1.000000       54501.0
#         81         81        0   0.989   0.361  1.000000       51811.2
#         85         85        0   0.977   0.362  1.000000       49374.4
#         90         90        0   1.068   0.369  1.000000       46633.3
#         95         95        0   0.741   0.366  1.000000       44180.3
#        100        100        0   0.886   0.364  1.000000       41972.7
#        106        106        0   0.892   0.362  1.000000       39598.4
#        112        112        0   0.932   0.361  1.000000       37478.6
#        118        118        0   0.902   0.363  1.000000       35574.5
#        125        125        0   0.973   0.363  1.000000       33584.0
#        132        132        0   1.011   0.362  1.000000       31804.5
#        139        139        0   1.878   0.366  1.000000       30204.3
#        147        147        0   0.888   0.361  1.000000       28562.1
#        155        155        0   1.028   0.362  1.000000       27089.4
#        164        164        0   0.903   2.031  1.000000       25604.5
#        173        173        0   1.077   0.372  1.000000       24273.9
#        183        183        0   0.920   0.362  1.000000       22949.1
#        194        194        0   0.882   0.364  1.000000       21649.6
#        205        205        0   0.909   0.363  1.000000       20489.5
#        217        217        0   0.903   0.363  1.000000       19358.1
#        230        230        0   0.888   0.362  1.000000       18265.5
#        243        243        0   0.885   0.360  1.000000       17289.9
#        257        257        0   1.200   0.360  1.000000       16349.6
#        272        272        0   1.403   0.362  1.000000       15449.7
#        288        288        0   0.915   0.368  1.000000       14593.1
#        305        305        0   0.926   0.365  1.000000       13781.5
#        323        323        0   0.933   0.366  1.000000       13015.2
#        342        342        0   0.931   0.387  1.000000       12293.8
#        362        362        0   0.889   0.367  1.000000       11616.2
#        383        383        0   1.089   0.367  1.000000       10981.0
#        405        405        0   0.866   0.368  1.000000       10386.1
#        429        429        0   0.915   0.368  1.000000        9806.8
#        454        454        0   0.875   0.369  1.000000        9268.3
#        480        480        0   0.898   0.366  1.000000        8767.9
#        508        508        0   1.044   0.380  1.000000        8286.3
#        538        538        0   0.859   0.368  1.000000        7825.8
#        569        569        0   0.917   0.366  1.000000        7401.0
#        602        602        0   0.987   0.365  1.000000        6996.9
#        637        637        0   0.888   0.364  1.000000        6614.1
#        674        674        0   0.918   0.375  1.001484        6252.6
#        714        714        0   0.983   0.367  1.001401        5904.0
#        756        756        0   0.860   0.373  1.001323        5577.6
#        800        800        0   0.874   0.365  1.001250        5272.5
#        847        847        0   0.963   0.372  1.001181        4981.5
#        897        897        0   0.883   0.363  1.001115        4705.5
#        950        950        0   0.968   0.372  1.001053        4444.6
#       1006       1006        0   0.911   0.364  1.000994        4198.8
#       1065       1065        0   1.088   0.366  1.001878        3967.9
#       1128       1128        0   0.888   0.369  1.001773        3747.9
#       1194       1194        0   0.942   0.372  1.001675        3542.4
#       1264       1264        0   0.864   0.365  1.001582        3347.8
#       1339       1339        0   0.908   0.367  1.001494        3162.0
#       1418       1418        0   0.913   0.366  1.001410        2987.4
#       1502       1502        0   0.849   0.367  1.001332        2822.0
#       1591       1591        0   0.922   0.369  1.001257        2665.8
#       1685       1685        0   0.903   0.369  1.001187        2518.7
#       1784       1784        0   0.880   0.370  1.001121        2380.6
#       1884       1884        0   0.879   0.375  1.001062        2255.7
#       1995       1995        0   0.921   0.388  1.001504        2131.9
#       2113       2113        0   0.895   0.379  1.001420        2014.5
#       2239       2239        0   0.858   0.380  1.001340        1902.7
#       2371       2371        0   0.884   0.386  1.001265        1798.4
#       2512       2512        0   0.918   0.392  1.001194        1699.1
#       2661       2661        0   0.865   0.411  1.001503        1605.6
#       2818       2818        0   0.897   0.407  1.002129        1517.8
#       2985       2985        0   0.859   0.444  1.002010        1434.5
#       3162       3162        0   0.931   0.439  1.001898        1355.9
#       3350       3350        0   0.863   0.428  1.002388        1281.5
#       3548       3548        0   0.879   0.434  1.002537        1211.6
#       3758       3758        0   0.934   0.450  1.002661        1145.5
#       3981       3981        0   0.908   0.459  1.002763        1083.0
#       4217       4217        0   0.908   0.469  1.003083        1024.1
#       4467       4467        0   0.905   0.477  1.002910         968.4
#       4732       4732        0   0.869   0.487  1.002747         915.8
#       5012       5012        0   0.918   0.499  1.003192         866.3
#       5309       5309        0   0.868   0.508  1.003390         819.5
#       5623       5623        0   0.887   0.515  1.003913         775.4
#       5957       5957        0   0.906   0.520  1.004532         733.6
#       6310       6310        0   0.887   0.559  1.004596         694.2
#       6683       6683        0   0.916   0.532  1.004788         657.1
#       7079       7079        0   0.897   0.535  1.004662         622.0
#       7499       7499        0   0.904   0.544  1.004534         588.8
#       7943       7943        0   0.911   0.618  1.004658         557.5
#       8414       8414        0   0.918   0.559  1.004635         528.0
#       8913       8913        0   1.030   0.614  1.004937         500.1
#       9441       9441        0   0.989   0.551  1.005614         473.7
#      10000      10000        0   0.930   0.552  1.005500         448.9
#      10593      10593        0   0.923   0.629  1.005947         425.4
#      11220      11220        0   0.929   0.556  1.005793         403.3
#      11885      11885        0   0.914   0.574  1.005890         382.4
#      12589      12589        0   0.906   0.583  1.006116         362.6
#      13335      13335        0   0.919   0.561  1.006224         344.0
#      14125      14125        0   0.912   0.576  1.006796         326.4
#      14962      14962        0   1.057   0.565  1.007018         309.8
#      15849      15849        0   0.903   0.568  1.007193         294.1
#      16788      16788        0   0.896   0.575  1.007744         279.3
#      17783      17783        0   1.004   0.572  1.008154         265.3
#      18836      18836        0   0.908   0.575  1.008335         252.1
#      19953      19953        0   0.918   0.593  1.008871         239.6
#      21135      21135        0   0.913   0.580  1.009558         227.9
#      22387      22387        0   0.911   0.593  1.010184         216.8
#      23714      23714        0   0.910   0.598  1.010880         206.3
#      25119      25119        0   0.901   0.605  1.011744         196.4
#      26607      26607        0   0.919   0.590  1.012553         187.1
#      28184      28184        0   0.896   0.598  1.013163         178.2
#      29854      29854        0   0.888   0.603  1.013633         169.9
#      31623      31623        0   1.012   0.597  1.014704         162.1
#      33497      33497        0   0.889   0.608  1.015554         154.6
#      35481      35481        0   0.902   0.617  1.016319         147.6
#      37584      37584        0   0.895   0.605  1.017481         141.0
#      39811      39811        0   0.896   0.617  1.018337         134.8
#      42170      42170        0   0.892   0.609  1.019753         128.9
#      44668      44668        0   0.893   0.617  1.021201         123.3
#      47315      47315        0   0.895   0.613  1.022678         118.1
#      50119      50119        0   0.894   0.627  1.024322         113.1
#      53088      53088        0   0.891   0.618  1.025599         108.4
#      56234      56234        0   0.937   0.632  1.026728         104.0
#      59566      59566        0   0.886   0.625  1.027734          99.8
#      63096      63096        0   1.071   0.627  1.029923          95.9
#      66834      66834        0   0.927   0.635  1.031825          92.2
#      70795      70795        0   0.883   0.634  1.033703          88.7
#      74989      74989        0   0.914   0.631  1.035152          85.4
#      79433      79433        0   0.879   0.632  1.037453          82.2
#      84140      84140        0   0.887   0.635  1.039458          79.3
#      89125      89125        0   0.884   0.636  1.042098          76.5
#      94406      94406        0   0.885   0.638  1.044764          73.8
#     100000     100000        0   0.881   0.639  1.047350          71.3
#     105925     100000        0   0.884   0.640  1.050080          69.0
#     112202     100000        0   0.919   0.662  1.053600          66.8
#     118850     100000        0   0.897   0.647  1.057100          64.7
#     125893     100000        0   0.901   0.652  1.059820          62.7
#     133352     100000        0   0.884   0.651  1.063240          60.9
#     141254     100000        0   0.888   0.650  1.067290          59.1
#     149624     100000        0   0.916   0.653  1.071780          57.4
#     158489     100000        0   0.940   0.657  1.075130          55.9
#     167880     100000        0   0.913   0.659  1.082310          54.4
#     177828     100000        0   0.899   0.671  1.085360          53.0
#     188365     100000        0   0.897   0.664  1.090720          51.7
#     199526     100000        0   0.915   0.668  1.096770          50.4
#     211349     100000        0   0.928   0.665  1.101930          49.3
#     223872     100000        0   0.934   0.670  1.108100          48.2
#     237137     100000        0   0.926   0.667  1.113690          47.1
#     251189     100000        0   0.955   0.675  1.119180          46.1
#     266073     100000        0   0.911   0.693  1.128930          45.2
#     281838     100000        0   0.918   0.676  1.136280          44.3
#     298538     100000        0   0.929   0.685  1.145900          43.5
#     316228     100000        0   0.922   0.686  1.153400          42.7
#     334965     100000        0   0.936   0.688  1.162440          41.9
#     354813     100000        0   0.956   0.694  1.172560          41.2
#     375837     100000        0   0.958   0.692  1.183690          40.6
#     398107     100000        0   0.959   0.699  1.193780          40.0
#     421697     100000        0   0.942   0.702  1.204740          39.4
#     446684     100000        0   0.955   0.700  1.215820          38.8
#     473151     100000        0   0.952   0.713  1.228310          38.3
#     501187     100000        0   0.962   0.713  1.241420          37.8
#     530884     100000        0   0.964   0.714  1.257920          37.3
#     562341     100000        0   0.979   0.711  1.272740          36.9
#     595662     100000        0   1.003   0.714  1.289160          36.5
#     630957     100000        0   1.015   0.722  1.303190          36.1
#     668344     100000        0   1.020   0.730  1.322380          35.7
#     707946     100000        0   1.026   0.737  1.341750          35.4
#     749894     100000        0   1.015   0.743  1.368090          35.0
#     794328     100000        0   1.019   0.744  1.384790          34.7
#     841395     100000        0   1.030   0.746  1.408600          34.4
#     891251     100000        0   1.045   0.753  1.434040          34.1
#     944061     100000        0   1.049   0.778  1.456490          33.9
#    1000000     100000        0   1.057   0.766  1.485870          33.6
#    1059254     100000        0   1.066   0.768  1.513600          33.4
#    1122018     100000        0   1.106   0.778  1.542830          33.2
#    1188502     100000        0   1.090   0.790  1.577200          33.0
#    1258925     100000        0   1.138   0.792  1.612530          32.8
#    1333521     100000        0   1.121   0.811  1.645650          32.6
#    1412538     100000        0   1.135   0.810  1.682130          32.4
#    1496236     100000        0   1.159   0.820  1.722840          32.2
#    1584893     100000        0   1.171   0.847  1.765690          32.1
#    1678804     100000        0   1.185   0.844  1.817750          31.9
#    1778279     100000        0   1.202   0.853  1.864700          31.8
#    1883649     100000        0   1.222   0.867  1.912490          31.7
#    1995262     100000        0   1.242   0.876  1.967780          31.5
#    2113489     100000        0   1.263   0.896  2.020420          31.4
#    2238721     100000        0   1.286   0.922  2.075790          31.3
#    2371374     100000        0   1.320   0.929  2.146300          31.2
#    2511886     100000        0   1.335   0.945  2.209570          31.1
#    2660725     100000        0   1.363   0.944  2.293110          31.0
#    2818383     100000        0   1.391   0.960  2.360800          30.9
#    2985383     100000        0   1.422   0.978  2.446730          30.8
#    3162278     100000        0   1.461   1.009  2.537540          30.8
#    3349654     100000        0   1.501   1.016  2.622900          30.7
#    3548134     100000        0   1.533   1.060  2.710860          30.6
#    3758374     100000        0   1.578   1.062  2.824550          30.5
#    3981072     100000        0   1.622   1.273  2.922530          30.5
#    4216965     100000        0   1.673   1.115  3.041830          30.4
#    4466836     100000        0   1.729   1.160  3.149510          30.4
#    4731513     100000        0   1.784   1.178  3.292520          30.3
#    5011872     100000        0   1.854   1.216  3.433090          30.3
#    5308844     100000        0   1.946   1.262  3.576600          30.2
#    5623413     100000        0   1.958   1.262  3.719150          30.2
#    5956621     100000        0   2.022   1.496  3.885680          30.1
#    6309573     100000        0   2.180   1.357  4.057750          30.1
#    6683439     100000        0   2.196   1.383  4.250390          30.1
#    7079458     100000        0   2.257   1.431  4.444160          30.0
#    7498942     100000        0   2.340   1.482  4.640880          30.0
#    7943282     100000        0   2.445   1.525  4.852800          29.9
#    8413951     100000        0   2.547   1.595  5.074780          29.9
#    8912509     100000        0   2.691   1.656  5.320130          29.9
#    9440609     100000        0   2.798   1.696  5.560000          29.9
#   10000000     100000        0   2.996   1.784  5.853460          29.8
#   10592537     100000        0   3.087   1.862  6.153020          29.8
#   11220185     100000        0   3.233   1.922  6.430500          29.8
#   11885022     100000        0   3.384   2.104  6.773630          29.8
#   12589254     100000        0   3.566   2.118  7.090330          29.7
#   13335214     100000        0   3.768   2.197  7.450920          29.7
#   14125375     100000        0   7.923   2.316  7.868460          29.7
#   14962357     100000        0   4.145   2.436  8.259020          29.7
# Total Duplicate strings = 0
# Begin HashFreeArray()...
#                      returned 444133848 bytes
# Free 14962357 strings, 0.312 uSecs Ave/string

# Pass 1
# Pass 2
# Pass 3
# Pass 4
# Pass 5
# Pass 6
# Pass 7
# Pass 8
# Pass 9
# TotInserts      0     0 InsTime GetTime      0 Ram/String
           1      0     0 5775.911   0.901      0 4194352.000
           2      0     0   1.096   0.317      0 2097190.000
           3      0     0   0.883   0.309      0 1398134.667
           4      0     0   0.846   0.311      0 1048607.000
           5      0     0   0.776   0.305      0 838890.400
           6      0     0   0.911   0.296      0 699079.333
           7      0     0   0.796   0.306      0 599215.429
           8      0     0   0.711   0.302      0 524316.500
           9      0     0   0.817   0.292      0 466061.333
          10      0     0   0.633   0.295      0 419458.000
          11      0     0   0.701   0.297      0 381328.000
          12      0     0   0.732   0.307      0 349553.333
          13      0     0   0.829   0.312      0 322667.385
          14      0     0   0.778   0.317      0 299621.429
          15      0     0   0.659   0.312      0 279648.267
          16      0     0   0.871   0.319      0 262172.250
          17      0     0   0.845   0.317      0 246752.000
          18      0     0   0.851   0.321      0 233045.111
          19      0     0   0.889   0.324      0 220781.263
          20      0     0   0.923   0.329      0 209743.800
          21      0     0   0.697   0.333      0 199757.905
          22      0     0   0.646   0.329      0 190679.455
          23      0     0   0.773   0.326      0 182390.261
          24      0     0   1.035   0.325      0 174791.833
          25      0     0   0.833   0.321      0 167801.120
          26      0     0   0.834   0.323      0 161348.462
          27      0     0   0.705   0.328      0 155373.778
          28      0     0   0.666   0.331      0 149825.714
          29      0     0   0.752   0.341      0 144660.414
          30      0     0   0.728   0.342      0 139839.333
          31      0     0   0.814   0.339      0 135329.290
          32      0     0   0.931   0.339      0 131101.125
          34      0     0   0.895   0.336      0 123391.412
          36      0     0   0.888   0.339      0 116537.889
          38      0     0   0.784   0.344      0 110406.526
          40      0     0   0.985   0.348      0 104887.900
          42      0     0   0.843   0.351      0 99894.381
          44      0     0   0.914   0.348      0 95355.364
          46      0     0   0.801   0.348      0 91210.609
          48      0     0   0.875   0.347      0 87411.500
          50      0     0   0.831   0.347      0 83916.240
          53      0     0   0.856   0.346      0 79167.698
          56      0     0   0.932   0.348      0 74928.286
          59      0     0   0.736   0.346      0 71119.932
          62      0     0   0.787   0.348      0 67680.000
          65      0     0   0.862   0.348      0 64557.723
          69      0     0   0.814   0.349      0 60817.043
          73      0     0   0.864   0.350      0 57486.521
          77      0     0   0.787   0.347      0 54501.662
          81      0     0   0.900   0.351      0 51811.556
          85      0     0   0.938   0.348      0 49374.824
          90      0     0   0.947   0.347      0 46633.333
          95      0     0   0.741   0.348      0 44180.337
         100      0     0   0.844   0.347      0 41972.760
         106      0     0   0.812   0.343      0 39598.604
         112      0     0   0.899   0.347      0 37478.893
         118      0     0   0.854   0.351      0 35574.508
         125      0     0   0.914   0.351      0 33583.840
         132      0     0   0.937   0.349      0 31804.333
         139      0     0   0.902   0.352      0 30204.259
         147      0     0   0.877   0.357      0 28562.122
         155      0     0   0.853   0.358      0 27089.394
         164      0     0   0.875   0.359      0 25604.463
         173      0     0   0.833   0.359      0 24273.873
         183      0     0   0.873   0.358      0 22948.962
         194      0     0   0.848   0.357      0 21649.381
         205      0     0   0.908   0.356      0 20489.190
         217      0     0   0.876   0.358      0 19357.862
         230      0     0   0.853   0.358      0 18265.443
         243      0     0   0.884   0.358      0 17289.745
         257      0     0   0.893   0.359      0 16349.479
         272      0     0   0.857   0.358      0 15449.441
         288      0     0   0.897   0.357      0 14592.708
         305      0     0   0.848   0.356      0 13780.997
         323      0     0   0.862   0.356      0 13014.625
         342      0     0   0.891   0.357      0 12293.158
         362      0     0   0.882   0.355      0 11615.613
         383      0     0   0.876   0.356      0 10980.261
         405      0     0   0.866   0.353      0 10385.363
         429      0     0   0.863   0.353      0 9805.874
         454      0     0   0.875   0.352      0 9267.436
         480      0     0   0.881   0.351      0 8766.933
         508      0     0   0.893   0.352      0 8285.331
         538      0     0   0.859   0.352      0 7824.952
         569      0     0   0.885   0.352      0 7400.239
         602      0     0   0.881   0.354      0 6996.252
         637      0     0   0.869   0.354      0 6613.495
         674      0     0   0.887   0.356      0 6252.095
         714      0     0   0.896   0.355      0 5903.445
         756      0     0   0.860   0.356      0 5577.132
         800      0     0   0.874   0.356      0 5271.980
         847      0     0   0.890   0.357      0 4981.096
         897      0     0   0.883   0.358      0 4705.137
         950      0     0   0.871   0.357      0 4444.261
        1006      0     0   0.887   0.358      0 4198.489
        1065      0     0   0.853   0.358      0 3967.485
        1128      0     0   0.873   0.357      0 3747.500
        1194      0     0   0.866   0.361      0 3541.889
        1264      0     0   0.864   0.359      0 3347.323
        1339      0     0   0.860   0.356      0 3161.422
        1418      0     0   0.860   0.356      0 2986.928
        1502      0     0   0.849   0.358      0 2821.534
        1591      0     0   0.877   0.364      0 2665.373
        1685      0     0   0.844   0.363      0 2518.345
        1784      0     0   0.865   0.367      0 2380.206
        1884      0     0   0.861   0.364      0 2255.410
        1995      0     0   0.861   0.366      0 2131.501
        2113      0     0   0.866   0.370      0 2014.101
        2239      0     0   0.843   0.375      0 1902.385
        2371      0     0   0.864   0.376      0 1798.111
        2512      0     0   0.840   0.382      0 1698.838
        2661      0     0   0.843   0.385      0 1605.371
        2818      0     0   0.846   0.391      0 1517.550
        2985      0     0   0.843   0.398      0 1434.277
        3162      0     0   0.850   0.404      0 1355.667
        3350      0     0   0.835   0.411      0 1281.236
        3548      0     0   0.828   0.420      0 1211.372
        3758      0     0   0.835   0.431      0 1145.315
        3981      0     0   0.836   0.442      0 1082.816
        4217      0     0   0.825   0.454      0 1023.862
        4467      0     0   0.844   0.465      0 968.220
        4732      0     0   0.843   0.479      0 915.636
        5012      0     0   0.822   0.486      0 866.150
        5309      0     0   0.841   0.494      0 819.341
        5623      0     0   0.837   0.503      0 775.233
        5957      0     0   0.843   0.511      0 733.438
        6310      0     0   0.845   0.522      0 694.063
        6683      0     0   0.846   0.525      0 656.970
        7079      0     0   0.853   0.530      0 621.868
        7499      0     0   0.859   0.533      0 588.692
        7943      0     0   0.848   0.536      0 557.414
        8414      0     0   0.856   0.540      0 527.846
        8913      0     0   0.865   0.545      0 499.951
        9441      0     0   0.861   0.548      0 473.625
       10000      0     0   0.866   0.547      0 448.798
       10593      0     0   0.863   0.553      0 425.316
       11220      0     0   0.869   0.551      0 403.170
       11885      0     0   0.867   0.557      0 382.254
       12589      0     0   0.887   0.553      0 362.524
       13335      0     0   0.876   0.556      0 343.869
       14125      0     0   0.876   0.562      0 326.281
       14962      0     0   0.867   0.565      0 309.669
       15849      0     0   0.871   0.564      0 293.998
       16788      0     0   0.870   0.565      0 279.188
       17783      0     0   0.874   0.571      0 265.211
       18836      0     0   0.875   0.569      0 252.031
       19953      0     0   0.873   0.577      0 239.567
       21135      0     0   0.877   0.575      0 227.808
       22387      0     0   0.870   0.577      0 216.718
       23714      0     0   0.866   0.581      0 206.233
       25119      0     0   0.874   0.589      0 196.347
       26607      0     0   0.876   0.590      0 187.010
       28184      0     0   0.871   0.594      0 178.199
       29854      0     0   0.865   0.593      0 169.872
       31623      0     0   0.872   0.597      0 162.009
       33497      0     0   0.873   0.603      0 154.597
       35481      0     0   0.870   0.605      0 147.609
       37584      0     0   0.865   0.605      0 140.993
       39811      0     0   0.871   0.606      0 134.766
       42170      0     0   0.864   0.609      0 128.870
       44668      0     0   0.865   0.614      0 123.302
       47315      0     0   0.860   0.613      0 118.054
       50119      0     0   0.864   0.618      0 113.093
       53088      0     0   0.862   0.618      0 108.425
       56234      0     0   0.863   0.621      0 104.002
       59566      0     0   0.863   0.625      0  99.831
       63096      0     0   0.862   0.627      0  95.893
       66834      0     0   0.862   0.631      0  92.175
       70795      0     0   0.859   0.630      0  88.667
       74989      0     0   0.860   0.631      0  85.352
       79433      0     0   0.863   0.632      0  82.232
       84140      0     0   0.862   0.635      0  79.274
       89125      0     0   0.861   0.636      0  76.479
       94406      0     0   0.864   0.638      0  73.849
      100000      0     0   0.864   0.639      0  71.366
      105925      0     0   0.865   0.640      0  69.019
      112202      0     0   0.863   0.645      0  66.805
      118850      0     0   0.863   0.647      0  64.713
      125893      0     0   0.868   0.647      0  62.739
      133352      0     0   0.867   0.651      0  60.869
      141254      0     0   0.871   0.650      0  59.111
      149624      0     0   0.868   0.653      0  57.449
      158489      0     0   0.872   0.656      0  55.878
      167880      0     0   0.874   0.656      0  54.398
      177828      0     0   0.880   0.661      0  53.002
      188365      0     0   0.880   0.664      0  51.683
      199526      0     0   0.879   0.663      0  50.439
      211349      0     0   0.884   0.665      0  49.262
      223872      0     0   0.887   0.663      0  48.152
      237137      0     0   0.890   0.667      0  47.102
      251189      0     0   0.892   0.668      0  46.115
      266073      0     0   0.895   0.675      0  45.180
      281838      0     0   0.898   0.676      0  44.298
      298538      0     0   0.896   0.679      0  43.463
      316228      0     0   0.905   0.678      0  42.674
      334965      0     0   0.909   0.686      0  41.935
      354813      0     0   0.907   0.690      0  41.231
      375837      0     0   0.913   0.689      0  40.570
      398107      0     0   0.918   0.694      0  39.944
      421697      0     0   0.925   0.696      0  39.353
      446684      0     0   0.932   0.694      0  38.796
      473151      0     0   0.939   0.698      0  38.271
      501187      0     0   0.942   0.706      0  37.772
      530884      0     0   0.949   0.704      0  37.306
      562341      0     0   0.957   0.711      0  36.863
      595662      0     0   0.960   0.714      0  36.446
      630957      0     0   0.967   0.722      0  36.050
      668344      0     0   0.974   0.724      0  35.680
      707946      0     0   0.980   0.725      0  35.329
      749894      0     0   0.999   0.738      0  35.001
      794328      0     0   0.996   0.738      0  34.687
      841395      0     0   1.010   0.744      0  34.392
      891251      0     0   1.016   0.748      0  34.112
      944061      0     0   1.032   0.753      0  33.849
     1000000      0     0   1.036   0.760      0  33.601
     1059254      0     0   1.044   0.768      0  33.363
     1122018      0     0   1.063   0.778      0  33.143
     1188502      0     0   1.076   0.787      0  32.933
     1258925      0     0   1.090   0.789      0  32.737
     1333521      0     0   1.105   0.802      0  32.550
     1412538      0     0   1.122   0.810      0  32.374
     1496236      0     0   1.135   0.820      0  32.206
     1584893      0     0   1.159   0.831      0  32.048
     1678804      0     0   1.165   0.844      0  31.900
     1778279      0     0   1.184   0.849      0  31.760
     1883649      0     0   1.212   0.864      0  31.628
     1995262      0     0   1.233   0.876      0  31.503
     2113489      0     0   1.246   0.890      0  31.386
     2238721      0     0   1.268   0.905      0  31.276
     2371374      0     0   1.294   0.914      0  31.171
     2511886      0     0   1.322   0.923      0  31.073
     2660725      0     0   1.340   0.944      0  30.980
     2818383      0     0   1.382   0.960      0  30.890
     2985383      0     0   1.408   0.978      0  30.807
     3162278      0     0   1.434   1.008      0  30.728
     3349654      0     0   1.485   1.016      0  30.654
     3548134      0     0   1.529   1.043      0  30.583
     3758374      0     0   1.560   1.062      0  30.518
     3981072      0     0   1.601   1.090      0  30.455
     4216965      0     0   1.660   1.114      0  30.397
     4466836      0     0   1.703   1.136      0  30.341
     4731513      0     0   1.751   1.163      0  30.289
     5011872      0     0   1.809   1.199      0  30.239
     5308844      0     0   1.869   1.229      0  30.192
     5623413      0     0   1.942   1.260      0  30.148
     5956621      0     0   2.013   1.299      0  30.106
     6309573      0     0   2.076   1.338      0  30.067
     6683439      0     0   2.155   1.376      0  30.030
     7079458      0     0   2.244   1.420      0  29.994
     7498942      0     0   2.320   1.474      0  29.961
     7943282      0     0   2.421   1.519      0  29.929
     8413951      0     0   2.526   1.576      0  29.900
     8912509      0     0   2.640   1.630      0  29.871
     9440609      0     0   2.759   1.694      0  29.845
    10000000      0     0   2.886   1.759      0  29.820
    10592537      0     0   3.012   1.844      0  29.798
    11220185      0     0   3.169   1.917      0  29.776
    11885022      0     0   3.336   2.002      0  29.756
    12589254      0     0   3.493   2.081      0  29.737
    13335214      0     0   3.697   2.178      0  29.718
    14125375      0     0   3.867   2.272      0  29.700
    14962357      0     0   4.091   2.388      0  29.683
