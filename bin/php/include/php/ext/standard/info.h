/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Rasmus Lerdorf <rasmus@php.net>                             |
   |          Zeev Suraski <zeev@php.net>                                 |
   |          Colin Viebrock <colin@viebrock.ca>                          |
   +----------------------------------------------------------------------+
*/

#ifndef INFO_H
#define INFO_H

#define PHP_ENTRY_NAME_COLOR "#ccf"
#define PHP_CONTENTS_COLOR "#ccc"
#define PHP_HEADER_COLOR "#99c"

#define PHP_INFO_GENERAL (1 << 0)
#define PHP_INFO_CREDITS (1 << 1)
#define PHP_INFO_CONFIGURATION (1 << 2)
#define PHP_INFO_MODULES (1 << 3)
#define PHP_INFO_ENVIRONMENT (1 << 4)
#define PHP_INFO_VARIABLES (1 << 5)
#define PHP_INFO_LICENSE (1 << 6)
#define PHP_INFO_ALL 0xFFFFFFFF

#ifndef HAVE_CREDITS_DEFS
#define HAVE_CREDITS_DEFS

#define PHP_CREDITS_GROUP (1 << 0)
#define PHP_CREDITS_GENERAL (1 << 1)
#define PHP_CREDITS_SAPI (1 << 2)
#define PHP_CREDITS_MODULES (1 << 3)
#define PHP_CREDITS_DOCS (1 << 4)
#define PHP_CREDITS_FULLPAGE (1 << 5)
#define PHP_CREDITS_QA (1 << 6)
#define PHP_CREDITS_WEB (1 << 7)
#define PHP_CREDITS_ALL 0xFFFFFFFF

#endif /* HAVE_CREDITS_DEFS */

#define PHP_LOGO_DATA_URI                                                      \
  "data:image/"                                                                \
  "png;base64,iVBORw0KGgoAAAANSUhEUgAAAHkAAABACAYAAAA+"                        \
  "j9gsAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAD4BJREFUeNrsnXtwXF" \
  "Udx8/dBGihmE21QCrQDY6oZZykon/"                                              \
  "gY5qizjgM2KQMfzFAOioOA5KEh+"                                                \
  "j4R9oZH7zT6MAMKrNphZFSQreKHRgZmspLHSCJ2Co6tBtJk7Zps7tJs5t95F5/"             \
  "33PvWU4293F29ybdlPzaM3df2XPv+Zzf4/"                                         \
  "zOuWc1tkjl+T0HQ3SQC6SBSlD6WKN4rusGm9F1ps/"                                  \
  "o5mPriOf8dd0YoNfi0nt4ntB1PT4zYwzQkf3kR9/"                                   \
  "sW4xtpS0CmE0SyPUFUJXFMIxZcM0jAZ4xrKMudQT7963HBF0n6EaUjkP0vI9K9OEHWqJLkNW1s" \
  "8mC2WgVTwGAqWTafJzTWTKZmQuZ/"                                               \
  "k1MpAi2+"                                                                   \
  "eys6mpWfVaAPzcILu8EVKoCAaYFtPxrAXo8qyNwzZc7gSgzgN9Hx0Ecn3j8xr4lyHOhNrlpaJI" \
  "gptM5DjCdzrJ0Jmce6bWFkOpqs0MErA4gXIBuAmY53gFmOPCcdaTXCbq+"                  \
  "n16PPLXjewMfGcgEttECeouTpk5MplhyKsPBTiXNYyULtwIW7Cx1vlwuJyDLR9L0mQiVPb27fh" \
  "A54yBbGttMpc1OWwF1cmKaH2FSF7vAjGezOZZJZ9j0dIZlMhnuRiToMO0c+"                \
  "N4X7oksasgEt9XS2KZCHzoem2Ixq5zpAuDTqTR14FMslZyepeEI4Ogj26n0vLj33uiigExgMWR" \
  "pt+"                                                                        \
  "CGCsEePZqoePM738BPTaJzT7CpU0nu1yXpAXCC3VeRkCW4bfJYFZo6dmJyQTW2tvZc1nb719iy" \
  "ZWc5fmZ6Osu6H3uVzit52oBnMll2YizGxk8muFZLAshb/"                              \
  "YKtzQdcaO3Y2CQ7eiy+YNGvLN+4+nJetm3bxhKJxJz316xZw1pbW9kLew+"                 \
  "w1944XBEaPj6eYCeOx1gqNe07bK1MwIDbKcOFOR49GuePT5fcfOMX2drPXcQ0zf7y2tvbWVdXF" \
  "/v1k2+yQ4dPVpQ5P0Um/NjoCX6UBMFZR6k+u7qMYVBYDIEqBW7eXAfPZX19zp2/"            \
  "oaGBHysNMGTFinPZik9fWggbI5Omb13zUDeB3lLsdwaK/YPeyAFU0i8Aw9/"                \
  "2Dwyx4SPjFQEYUlf3MTYw4Jx7CIVCbHR0oqIDNMD+FMG+ZE0dO/tsHlvAWnYS6H4qjfMC+Zld/" \
  "wg92/tuv2WeeYT87j+H2aFDxysGLuSy+o/"                                         \
  "z49DQkONnmpqa2MjRyoYsZOXKGnb5Z+vZqlUrxUsAvI9At/"                            \
  "oK+elnBpoNw+Dai9TekSMxDrgSh0KrSYshTprc2NhoRf1JtlikqirAVl98AddsSavDBDrsC+"   \
  "QdT7/"                                                                      \
  "TSoB344tzOZ39+70RbporVerqasyw1MEnC8iV6I9VTDi0uqbmfPFSq2W+"                  \
  "gyUHXuEdb3WR5rab5jnD3i/"                                                    \
  "BNMN8ChNaqsTiKa55KmBWX+Tuj0XQdQVF307nhTH0CPls+O0UPbaT5TQG/"                 \
  "8qX68u6LpV67LQ6dNknaYgaYyPDx2TzvYGCsnhRkH8b/rsF2GDj1MCInkvxvRjOuCUlipWD/"   \
  "zrKx7ZOwBF0vfSSM2ShyaqAAOC1Nw+zt9/5YNbrN1zfwIdpfgnqebv/"                    \
  "A6pnWAn4qlW1HPgHQ6OeoG3N9RO/"                                               \
  "+StMdDtmV2LxJPfBpQCGfwTgrVu38jFrKaW2tpZt2LCBdXR0sEgkwhv21u9cxQsyW3ZB1+"     \
  "DgoOM54btU6tu8eTPr6elhy5fr7IZNDey+e76e9/"                                   \
  "fCLcAllHpdKKinpaUlX8+111xB9VzNrYxqUAY/"                                     \
  "XVVVJYMOekLu2fFGM8VWYQRYiYkU9bD4vPlHFYnH4/"                                 \
  "zvkb1CgwACHgMoUpdyw3sFXcXUh4YHaNSHDqaxdL5jwVTXBpeXVY9oF3RcUQ+O09NT7Cayfld+" \
  "4RJlP42gTIq8w66Qf/X4a6FTSSMMDcaE/"                                          \
  "NhYecMM+"                                                                   \
  "MdyG90OAhodWoAGkTUaSZByO5WdiA4GqwStrrM6k5vFKEXQserr63l7oR5V0NBojKctaSZtbne" \
  "ErOtGmFxwkGewjk0UzpCUlJSIRqMcjN8CkHLDqyRByq0PEGBBhDmdj7rQVujAaLfrrlk7xyW5g" \
  "UaxpEtOmOQDr0e799NYmDVBi0+"                                                 \
  "OT7FcbsaXxEQk8qprEBQMBm0vVKUBRcNjskFE8W71lSt79uzhda1d6w4ZGTUUp3NWAQ3TvW/"   \
  "fPvbVq+rZH/ceULOcF1/I06CY3QJohCCzNJnYdgEwwvpUKuNbUsLNpO3evZtfSGHp7+/"       \
  "nS2pw3LLFPVWLoA5yHQUtXvXFYjH+"                                              \
  "vU4F5yOibzsRUL38MTqC3XWh8GCWziMcDjt2BNEZUIfoUOpJkwvziT3S5ua8Jj/"            \
  "4yD5E0yERbPkhKv4RF4mhkN1wCMHN2rWfYZ2dnWz9+"                                 \
  "vXchNkJzBoaQ8Bxqg91wWo41YdO2dzczD+"                                         \
  "3bt06Rw0rBG4nOF8oi9M0Jsw9OgLqQ124BifLgeuHyVbN0NXUrODBmDWxgRR0pNrUYqMNgDOZG" \
  "ZbNzvgCuc4j0kX+GPJ2//CcMagQmKkbrm/"                                         \
  "knwVEp++SIXulM1+nhj9AY207QRDnpsnye24WA59DkuPlV/"                            \
  "5j+z5eB2hE0W1tbTyQdNJmDpksRzFp2E9csFJAboRvDvz8gZdJgw2ek55KZphfAv+"          \
  "Inu8UdKnmkEUHQK93EjEZ4Rbkifq8JiactEpYAy9Nli2Gm6CjIZPn1qlKFWizleOG3BIwdKNZ+" \
  "KRMxr9VHKvr1NKLXo2BhlAVFRPq1qlWW6MBr3NWyY2rTGXO5ySJlN9uDuiGsV7XTVPtl8CHYGi" \
  "zf/9+V5Om0hAwVV4ahuU8qia03HP26kyqFkMOTudDzjs/P/QKBUiBYa5ZNucfZJUkCG/"       \
  "0IhpCxYyqBF3lnLOII8q1GKqdStQ3rTh5MStwXX5O/"                                 \
  "nE1metGQzPHUH6JatA1OppQ8u1eUbpX44tO4GY5vM5Z9sduFgOfG1GwUOK6VFzaSAmrWCSfzGC" \
  "uuT/O+bi6QwRdTtqXN2keJ4/"                                                   \
  "ejgkJ5HedRARkbkGe6ARulgMWQ+"                                                \
  "Wc3cDAWohhoZdcue7ifJ7crfP6Me8dELd0Mv8U2begC2k9SHd3t+"                       \
  "NnNm7cqKwRbiYUkykqvlZlmOYVLIq5bHRep46JzotOc9BhuFc0ZHGLph+"                  \
  "CJIaXr1FZSIfxsdBiN1+"                                                       \
  "LpALEK2By61Aqs0rwtV7DNBU3BMCYixYTLU6C8bM5hBwum0k1mesBpmPtlj+"               \
  "qXFenFsAgCVLon9DYeIxUnmh05HCdBIkCVRP6ussiepVZJZXIutCHwt2I0YGY2Kiz3AIyeG5aL" \
  "NooVULQBbHy1/nAK2oEtEanheil+GO3aFg0FnwSilNC4q6OrXzywc0XCy1WMaFu/"           \
  "tgrCBLRuWpHuP+n1zqmRXFN0GAnwKgHeW1E1C/"                                     \
  "86UDJHFKptATZMPZTafbLXHtN3OPixKRC4ev4GwB2Gy6JxhQNEYul+"                     \
  "KoKp79RMaGqKzy9ovzt27c7pidVZtYAGJMYOP7u6bdK1mLI1GQ+/"                       \
  "ogSZBahwKuLO2jSZt0odw65xrUhAMNrZskLsGiIXz72F3bTjV+"                         \
  "ixvtbWcMQr3NWCbog5VyXAIy63PLrqpJITIqHkcD9P7suSiYbG53wvTLKDbr8WBbjZqIF4F3PD" \
  "3ItRn1eQd5CBF3lCM5RAIYfVp0/dgZ8SvbJ2/"                                      \
  "l8MmlvNw+8qJTjm+drWQwaAXO9KMuWncc1GBMXKkGeV/"                               \
  "pU5ZxFIsTvzovOCu3HvDnOE7NTu3rLr+PE8fy6+IEX9947YM4n/+LbPT/"                  \
  "88R8QqoYAuVSDrZLFKcYso2AcLBIeGDPu6h3M+yqvIE/"                               \
  "4Y6w4LdUfi+jcr86L75KvC9+PcbVfd1hCi6U7Innwk1/"                               \
  "+Q5rcoetsdyBg3s9aCmivBsNFifGfG9zCJUFiztmpEXAbqhMgr6SLWBPu9R1enRfm1ktrC6cVY" \
  "WH+/Mqg43x6sYK1edaCex7vkRZHZkF+6P6NkXvvi/"                                  \
  "TpLNBUaqTtdcsoLtIrVTcem2EHDh7m2uq0ikMINBvafOmazzt+"                         \
  "BkGMW9CF70DndPsOaJqb38Y1oXjdCYHOiqwbPofrKid6thMAlnxxPtMy6w4K0ubNhq73U5wd5P" \
  "tVleCTd+"                                                                   \
  "50D2CEafLloqixyv0ufMcOGq64CVaMYN2119gfAdPpuscKOxWgCMDwxfm0pvzBhx9siRLoFt3c" \
  "a7Ikf+x2yygaYzHdTSi7IT9y8fMJ2Lpdhg+ZCPA2+f05d1A88mBLHzQaoA1dL6ohVLJGi+"     \
  "1uQj8XQMyHIMgaGT6eDxuozMkD294LRaB7CPI27DLHQSskSFRvGa30O/zndF4fF0DMhwa//9//" \
  "iZ2DcILqN7xBHn1oUweNn7eJ3WO9QHvdMlrMsphKEj8XQPgpuHVVMtGOgF0hC9CGTqbb2kHOzX" \
  "x73aKiuiymEv2x22ICMYYeWSALBQ7RQ0fkoZIr4DnRtS3ohzf1dNzTG9d0PcwMLahZO8UyKTMm" \
  "38wteratSVtkplq4oWj0PcfrEinPhYg14H+hvdIwCVs1bvb6O+"                         \
  "UBMYFGl90d0LRGLRDgoHEUwYnXDniQStocTVUwfPLaKQGA/"                            \
  "RoWOmkvtnsaG8unK+PWMKlH5e+"                                                 \
  "Lznp03N27RdO0TkxmYNZKszYBlyfI3RpjsQkmMOo8ls4Wsx1EKcEVAEvayyNoeRzsO2RI+"     \
  "93PNRLesGYtNpBhL4l/"                                                        \
  "prlgZz5ob0mbtZVFhWC301d0EuQgAHPgS7D9hssTHKyMbRfLptF213NBDRuoaqxNA2yh2VUBDn" \
  "xJ1M1yRW6gOgt2x64gqXK7ht1yOWyW1+"                                           \
  "wl7bYXvhUygQXgit4KuVDuBGzSbA2bmmtayNzpRgJOGu7XosHFChZzvrGTiUKt5UMiVsmbmtsC" \
  "b3+2lZmwm3hFNsA/CiYdKyfhYx3Aws8urp8nsJM72naGCG8zYwZMecjk/"                  \
  "WHVVRbsMwU6tBVQsWJS2sNDlrgVTO0RE/vzKQtuN2+/85k5PxlUaL75D3BZwKss+JUqSFRAO/"  \
  "F7Eqlkmj+2gbrgYE8rZFluu+P3pOGsyWCG/Y9/GR8exC+vYfc5flxgzRdDGsDEz/"           \
  "8AJsxwQcBUKPCtmKOMFJO8OKMgF8r3b3sKkAm69TN+2OZCAm5ID/"                       \
  "g9XPypwX29ufWgudq0urrKes/8nPkxgy1bdg6z/or/SFc2mzV/"                         \
  "xs+6HwySTmdYJp2dpaWKEregYrVfn9/B0xkD2U6+e+sOaHqImTfLrycUOIZM1hJwC3oemPXbi/" \
  "y5PnsrJ136bUa8pxu69BklmANWwDRkgR1wmwVaglyi3Nz6JLQ+"                         \
  "ZG5NxQsgNdAhmIfJN7wxgoWg9fxzPQ+c/g9YAIXgeUKCyipJO4uR/wswAOIwB/"             \
  "5IgxvbAAAAAElFTkSuQmCC"
#define PHP_EGG_LOGO_DATA_URI                                                  \
  "data:image/"                                                                \
  "png;base64,iVBORw0KGgoAAAANSUhEUgAAAHkAAABACAMAAAAJUSgeAAAC+"               \
  "lBMVEUAAACtsdVsooH18+"                                                      \
  "vP0Mfr5tahp3G3toS4wricto5JTIuoq9BZXJlgY55cXptQUouqp3ZkZ6OanciBk19RakXw69tI" \
  "Sotzc0dJS4yfpHB7frOusdZ6fbSprs5qbKfv6djv59T07t/t6NWNkMF7qY6ssIa/"           \
  "5Na9y6K0v8+"                                                                \
  "mvJZ3e7NISow5aEZGdU9Qqpc7b0lRr51QjGg3b1F7frRatqRYimZPhFtHakVRfFU/"          \
  "c085fV9z1sWY2chwx7Q5p5ig28p52clWsp5yzbxnxrRjwK5Gb01fknBXiWBGopNbj2hQh2FKfF" \
  "NCaUOm381OppFHg2JQgmIyakovZEbD69yU18NQknKJzblku6hQn4lCellSSjZyonxYj29Lflo4" \
  "ZD7G4dI8saJYnYBpl3E6hGjM6Nq05taB3MyFyLFLiWxDb0i75th80cFfWkRUUD+"            \
  "p5NU3m4eC1cOAg7dbu6o4dVZBYTy53s9nm3xHRjHR4NWL3s9LtaVrrZFPk3tDknhimHNBeFKv4" \
  "NCa4NDp4s54qINmnnVZlnNNeEva5d2L1cO1xaxucat2t5xYmHpokWZagls2Xj0tTy7e7eGGirs" \
  "5oJBhkGphimNGdEmTzLmAr41FoIpFl4FCinGWmsWk1L9bgFNabko/"                      \
  "Y0NMZD9DOyrT7uHK7uCV3MyL2cnK1sds08JlzLxxvqiMuZZZqJNco4k1k39SbELu7OCh49Ss2s" \
  "m22MaOj3h7zLl8xKpui11lhVcvWzg7VzZfsJhiqYmhlHyBfGZvZ1MlYkidoI5Cf11We06Okr5l" \
  "aaRCq5s0iXKDmmdRc08mVzqhpc2yu8xxm3M0Mx6dpcPPyrWlxqOktZuMsIZIi2RpdV3c2sunqZ" \
  "qPhmnF09S7xdEweV2AdVjc1by40LiWnKzJwKi3tKRyfXFTwrRnuZ2YwZpwlGgiQimHi69Dua1s" \
  "r5tUVpTEzLuZwKytuK54faKyqI4qcFdIXDagpbR5govMuJaSnYF9n4CkyblBRz3+/v/"        \
  "DqYZwXD8UFA2nO9FlAAAAKnRSTlMA/v79Iv70aP781IEnRv6VSXBf/"                     \
  "Ovbt0rv5NG8r9jMxa+KTc/"                                                     \
  "CjsSj2soo+"                                                                 \
  "frGAAAUlUlEQVRYw6zUbWgScRwH8BxBM9uiXkTQw4te9HDZg9mkdY0uVw6LimY641ZyzodhcGh" \
  "ReKws8Y5KjUrGlFIIfOjU+cLJBsN7NfRNGrbpG33hiBwMRnvTm172u0PoRTXWw1fxDoT73Pf+"  \
  "9/tvWDMHxB4cp/2jN26q1Vxr6A5L7d8ukeyCiMrP5pfS6Rmr7ukZs+GgRLK9q2vD/"          \
  "8vGQ1Wcpl0g9w70cPnWuX4sKxICsDhdDYV8qb5pe9xtKxUKgYDDsXv3tq4t/"               \
  "0PeBJVdLubB6NyJSwqayx89z1INUalUCodXxeB6OsZa/f1KC2VugMzTcgRBvMD/"            \
  "a+UDVbzDpRrWvhm5e+KRipu8cjKJVRA+"                                           \
  "iwvVkMeDd3D5oX4lhrnvhRFEDhFkr7dY3LvtX7rvE8Miq4Zlo29GTl+"                    \
  "TXuT0r4dYNMhffHlBXMXhTzrDtfqUKEqRZQewbZqXi93d3Vu7/rKxpFOM0y61rHa1Vhu5O/"    \
  "joPkMMKe1nw3K5YxFgGu+g/ZlM/"                                                \
  "nwSZS1ZWwNShlTChYAD8fL0ysrOv8C37xKJVqseXpbNzdVGZT10Oh2cemw2OcvlToCNrvs0zRC" \
  "T50DGYKWjryBRU9TkdNYb5UpA7vUCffjw5q1/"                                      \
  "9Ngle0SQhRDuYhjtqMwV+hLJ3TMYbBqISWNoejxGtYoG2Q+d+"                          \
  "1AMo0ibJhaNRmMam8Zk0mgMdQEvrhyGrL+"                                         \
  "4hGdLgWWQaYbpENjHU5DLEJIkI2n8Q89NhZGXiXyqD0VRS5bMmuG2bGY+"                  \
  "JGk22wTc4e3m7R1d63bDDgQRZE86kstFIsFgUKfTXb9+Jh6Pn/"                         \
  "3iMY4rjhwx0owWOqeUtzGQLyfiWbirLB83FY+7SVv0Sb0BF4LivL0+"                     \
  "V96enPRSJDcFrs5qtep08AXafT1kHB+4JJWOgwyd4d22oFiWfJpIUBRlsVDCLxzdZnj+"       \
  "TiiOeAV7zfXeuKftQuRf5581IwI70w7409O69Af1gKJXKlXBqDMEl7rNQmcSZDsGgdcNPiicWd" \
  "y2WDQWM9VL4QBv79y6ZuG2Cyl0NpvgWq0zqVTL10r5fL6xMU6v5/"                       \
  "DnA5ceHRscBFnNZCZPJlmUxchsIpGww4pjQoQjzFosBr1fPalXHEWovXnL7wuXHG3X8RXgb0Go" \
  "C25rDMJxHOF/OHJaNt6jmDg2ODuoUqnVDKE/"                                       \
  "3q9Ek1jWbYfnDKIlYb89jbIo2BaK1Ag02OUC0g21t/1ygktQGGlnebX5bH7eOuODtq1JLsP5/"  \
  "QRBaGuwmfUOKE5N3Jp9/0Klksm0D/THz6MA/ZDNJkMuqAQazt38sEFg2OsVuZefsF/"         \
  "BpVKg7coXO8FdSvuErpkMQfiv9g4zWthF7167dWFiQnpr9uVb1zDID/"                    \
  "XHPyfZJMiYILMW08dP795ZlSwEo7IwXhoI2M6KHOF3lp+W+"                            \
  "DvZ9RLTRBSFAVhNTNSoCxcujDu3lFqkFbANQktNWx5teWinLRNrMdbOGB5ppwstqCHDGLRiCL4" \
  "w6iQyPhYqHTRqpmMJmoAWEaUtBpFqjJtCiEbQwMJz+1CjdzHbL/+595x7B+DsDp/"           \
  "7BvBnBIMJajvktdUXwBgtAvlRoDynPvAoUKCVGY1pufTWzeM33HCe3UgWMII5rwJ6124IDasB2" \
  "Wn6GdD/"                                                                    \
  "wX+O1lwq8B24BPfXaq2Li4vezk5b+U4ZwEV5JvPIo0AgMHw64pAbjYeOXXz+"               \
  "6dYt9a77fW63W6UqLT3oDGPk+PkBkFP08fv3G6DiELvLB5v5L72p98XQ35WGwOCu8mojvCAI/"  \
  "IJVJrsWMA5CZCSfPRs4E4lEtHIFkrc331Kr3UfQkIORUzdQnSCx8HTdgLuxsTHV1rDZIKOCT8J" \
  "2ngL6b7j3N/"                                                                \
  "yNScMXVnm9jodxYen796U4L5cFHtstRS0teeaRkZGzww6vwwFdrT90tLJEo27WNLbNhRfCsViC" \
  "C3oSGBamcc+Vmpo+tG4ch9BOWHDIXzalUm/+3U69vVDqLIwq/"                          \
  "QZufb9W+3FqKg7y93joTJU0x97a0mIygRywd/v9WpALFFVHK/"                          \
  "M1qu2avv4JlqIwkgxxXTMYSfDhRJLD+2uUSmVKxseTnA+aayU4QGeba9sf+APKC5W2Wr1+"     \
  "3RkCY9nlJcg8UWCB1ZKXh+"                                                     \
  "RHdptOa9M6us8U2KuO5jarVfnqvv4FPh7n40BHZygMI0EPMT4PDtmLK0AOiyLP+"            \
  "OCUgQKNvT5d66He7Pz4wCAXAnu9Xr/"                                             \
  "8KjvKYpiwJCxPSCBvC5LNZrNdC+"                                                \
  "0kg8wKg6HqaIlGpckvvYHTPhz30TyGJWYoSpwXQiJBxGg6meQ4n7PaycV4KCBDv0NUtt7bhoay" \
  "8NzrOxcAPrnK29kuM5Kjo6PssiCIxHCKBfjpU7Pd77fpFQqtQ243tFZdys1X7W12V+"         \
  "DBuo7GDmeMwgTIzNO0jwuRYnR1iBBD4aTPiTvp6Pv5+"                                \
  "PQkWKjeG1KRh3ZkB9f4HeTCG8hmk1XZH4OMTU0tE8OStGsC2QKPUZtMoXdo5Xa7ZRBkdbO6ry1" \
  "4Xg2vUE+MZePzFBbGa4rpMIaNnRBh7zEoPN4AHR3lGRyVGybKulTkzOhqiq3NwlBPxaCl/"     \
  "AuqNnb9bk8hcqHST5/"                                                         \
  "mab3ttTaZUe7tVhgslsFjuSX5+aobV2brNBlZQLJnoNEpgBwVscTYvDAlMh4YpNPiOP4SUc/"   \
  "QTq8/N9SUuSPgJWu1rrJ64fGlk+ktrZLyx4+/Xr/"                                   \
  "rkoKbkU1yr7czJTvkCmizomOVJSUlpcWzsyqNWjUwKbDsvEBhsaCqw8djRPQ9QXA03RWd4vG2h" \
  "sNzxFrnu5SGBvimc5nI3xjUSw44W3AH7ZHr7a2FhRJXmaRHKjXlSeGDNlkOBemsra09pNfpFTB" \
  "ZDlzKLcnNd1fM/"                                                             \
  "tir0QxcSYqj1EycwsavqDt8U2Ro9RhJBCuOVHcJItdw2Bkmx52TKW4jlHsryOlNXot6SeuHPt4" \
  "j37NHATB4hfDNMZmQbIbTZYU3YUqWwXak5Mrtlbc7+tf4Zmd/"                          \
  "BJM8yxJjIoXNnVcrfSLJ30tgE0FlRQMtEMm2w3iIYJz0q0y5V2w515T9a4g4HFBnnVxvhGWXSK" \
  "UuqTQn/"                                                                    \
  "UXLbC50LEbaZbWwZHq93ZKVVcofieiaWIwX2VFKeE+"                                 \
  "wJPNA3cYRVPiewPLBmuI2X4iYbjvMkBPB6q5U6FMgN4GMIiO4W6eDsGgV2C2tPT0SF5jSsrIyV" \
  "z3IgRy5NeKQvX0LNpxAQ2FL0YHLlypz99VV3CFIjEWLXODGMJZYc1uFJ0gqsTpEjfcriz2cSDL" \
  "9QZ7iPfBAeoloJDeln3trFyPdOmABNRgMEkNrocvlKiuT5pTDtwcuxvp6RSTi0OmrkNxug3MA8" \
  "rFLFyufKPs/kj9//"                                                           \
  "iSJj2GGo6MijNDbbqdAkVyUEKNcMOiLYSLnYQjyNRyzavzFjqycifyrDXuPabMKwwCOsKnxbtQ" \
  "Yjfeof5BSC6MUsKUWyii1tynQkkC5altwA1kL2ot06Fi1tGWBwkqVtibzgmUgCmPdxAwUVi8TL" \
  "0wdYxc0zJEpG845lyzxeb+y6XRnrFm2ZL8+7/"                                      \
  "nOe853XPlcwKWAISclZRh4MsSVyXi8XINMpvW0VlZWrk1WjivRwUqSpWkkA/b1Cc/"          \
  "NXItxGMfj7m7TlgPTB14Q8NHOxlqONn08PX3y5PfPNZ0te/"                            \
  "vDpvkP7Dgp2E2fMPIayLHI3jypVAU5qSspKTc3CRxkloyHgS+"                          \
  "hNXgrKzsReWMx3rNwShgvRmSNQuET2LfNv03H8WF0s+"                                \
  "yiN4ZMpu6cTYMtR6cH9775HI2mN2dOvoDIv9qRuYYvx5ZFT9gayL98/"                    \
  "+2XnXl5eLDQl5AXMsG8gQEGpg+"                                                 \
  "Zm4HTilMyiGZkf48mrFEUDc3Mn0s1N5jNk5OTDbSshwU59fbqrYNbxtYfO/"                \
  "bhoefWz7z6wsmxpvkh+QZEdmw3fUXyPZDX/"                                        \
  "P7Nn5XePJQak9xMMAYvGAyFBgYGQkZGjroAc1WlxSmgS5XjzcUbM/2a3eGenwt+/"           \
  "Wu+O9VsNmdlZXVwRBxOakNDg1hQK9/69nMzb1MHP3y47IVj6z/"                         \
  "+Gi9Hz9QMDb+"                                                               \
  "14eDzkG8lGZG97rQn05kpxiDYGAQN2dgeCUH2Vq7N53JVyuIU0M3NzRnNMTlcNPQlZDMG4A5OK" \
  "oeDfpoqashxVB9r+nMIKWtMQtPW1dOHTYxcMOzYVPPFTdfF3ZAIee++"                    \
  "BbebQVdcVBey0RgKBELL+9uDvChqzeVK09DZ0FUM1GFI7tf0CU17z/"                     \
  "6mM5eXM7KEw2ZzOGy01BxH2dj6r4XvyzH4BabqrdV2uVBYY9KNOLY/U/"                   \
  "07jr93J6755ey+"                                                             \
  "Ba87Pb0VLDqmAVNslMkAGyk0tqx23ujCWtpGsEs0ZyQ9SXpzsd6qqegvkttNpqGcE5Ans+"     \
  "rqYjJ+OGLsVh9+QK+Am4T8ArSTZyDLn/7A2VfE31Dz4/"                               \
  "VxcbcyssudHsVDTaOri2QPRV5eHhhY3t8UikRdLsAqpYpWXSlqjr6q1LdV2BYL+"            \
  "OKffvrpREzuqFOI2Ao2cJG5wYGDrhAnUpzEIPOFckS2V5+zOHUFOBQ+"                    \
  "Gkehj5xdcLnd6aQacknm8YKRiJHkEOCBaK7X5erkSqmtYslLVUpl82PNSn2hvkInFGSVl5efMD" \
  "OypE7ClkgkbHZqKp4xh1xej4Mw6Jgs5AvLfvzV6dQ5+JgAyDcm7o0VG+"                   \
  "Xuoo6FyEFPpD0SCYWWmwAHoojsQj8HqlQqpVJszMUodluJ3tJdwMEjXX6iPCvLzJFIOiQKkjmp" \
  "arU4J7s2W5AjyAaNYmPw+fayr4685xyhl2FHHIXei2JDxiPWhUmmRunx7NrVHnj1+"          \
  "7GmSGggwItSS0fmNKn0u2Rp8nhGCp5t1WZ9G0W+JJslEh9+"                            \
  "EFkEWS0QCMRicUymxAX8obKDzz9/"                                               \
  "ZNuIrrugnpFv2btvJ8H0fD1mkLFYsFnBYNP3CYlnAqFQiKfN7exU0dYphYzeiaW1LiOjObnQ+"  \
  "QafIk+i3pBT2b4eDRIzMg0m+bvZ9Tj8InGB0ERHzyPbtqHgw9mMfNe+"                    \
  "nb0k02a8siUGjZELCVsSl2Ygo3O6IHdyyU7G0CvHM8eLM5L36N7o6+"                     \
  "iADBqyGHKPRMEOY0GrUzFEmG1cHdU7kBm4vewgtqmlPxvj9zhHBCRfc/VtkFFqsBfhoHH//"    \
  "vMHExPnA4EATyvDA+bqRCvBwNacrC+06jeWNjrf0Pnq/"                               \
  "pEb2D4bOnl49+7dIvQyDBG6WU52PdEFfHkNIuPm4kxjYYXF2bcij/ZOdAHGSS8ma4PLF9af/"   \
  "zwR5SZZO7qw4OrspNT5+"                                                       \
  "QxsLVQmO7uL2HV1HZJYuSfNDZyeKVuPhmRS2WymkYqzayFTZDqD0Rvdw41W0Jfk3tZWHOdT6Lx" \
  "F8xxsunDmPNVmJhAY0HrcC6BdXsw1RgldkukLLd06wERPTqJ3chrEHNuUTaMBrFCQjA+"       \
  "UXCwYdjiwquxlP77OwHGrHomvqLBcrPYoZBxuceii1wiW1rj/"                          \
  "wrXnEzHOQDZ6DAsLO12uvLx8wPmbN5colW0W3YgErg+yhGM2Y07VYb/"                    \
  "fpgkv7g5rNCIRZ1LBxl9CxiMWq/XFN/dV1zwc/3BM3rdz1D3RinpjmgFDXl7/"              \
  "Fx4wjKV5KnfQi8iUWcrloo1Kx62YKd8Okn1YwKIGtfpntVpT5bftWVxc7NdoqIUycgMyQ6bHa8" \
  "2l2wrYt/xLTk/Hw53CZF7Hmtly/"                                                \
  "vxVgBEa9TYaoztdXlenNy+PW7K2RKUstDjDO3bUdXQA7pCw1WLBSJ+"                     \
  "6T1Nls1oAV1RowmEOWwIa+zXNM85iP/7y/"                                         \
  "xsakjHR1ElQbS1lDs588vrr5K7MtNE4MTrq9XrT3NySEq5ys2VRs4NkVFqBJ0k9XESXV9Yqaz9" \
  "gq7WiPxwOS3wKambi7Ox6h9BuAoxbqSvIE3jCMDJYT62DLJtZAhrLvDM6EAgZta29oJFZpeLGO" \
  "y3WqR09VGc2XPQNuiHsW/"                                                      \
  "T7KxbxT35rxR5csfh8PoUIcg7mWW76HVfOsP4v95Lcit94oUhZx+LNX4SXzrii2CxlHg/"      \
  "P7cXgqvLjt+F/t2H9KCgvRyRS95E80o/ITkubHzLuk3p6/pH59nOf4vbxynIrDfA01yn/"      \
  "lhfcE7wVmlJzX3o5vkRZ5fdPYe3uqJNIJtkxuWikwt+/"                               \
  "aCnR+1HttkI6DyvYqSuy6d4r3rg+"                                               \
  "AhlmV2s6Bs5DxRmQX7soe9OjvKAxFOWxtLKo29vJVWWknJ6drZqawjyjh5jN6JHDkJ1W6x5Lid" \
  "JvbdvcGF+IZsY08J9zBLUOedn9Dz700KpVq64gU7WfZORSKTYEyK/"                      \
  "F7DPu3KARgxc1sDwerYyFkTKbWUVux2T5iRO4lHo3uxbV3oO0+"                         \
  "swqNFalHpEVbIUEshrw9me2JCQM3nHH/Q88+OCD9AVo/DPPUCnxuD5ZX/"                  \
  "zY7TffBxo4ZIN2165IJBKY4Gl3YXhYKXifggwa+yPkdx5/"                             \
  "9kWHztmmr8rEV9JDr8J5OHY0EVNkYdnWwYTBwcHVNO7AN7j/"                           \
  "gQce+I+clvadvrCk1HD7nXE33Er40oduuuRsb2+PBKI8GdmsjGa8OE8xobPKQeOWcZNQ16/"    \
  "PPH369GzmLGbCb4OMdkr3CNmP1wurB2PygenpubmW1fRrNbNLrqzndCyY/"                 \
  "M2471MlQcYAvrSvl5GPHz8eGp3oYuHPTz2GY2cmExqpKTTJFiVuUTBOk2vzSRRYyjk5775bW/"  \
  "vEW3JEJrnl1CFc0xxtYUZsf76N5F53njT/"                                         \
  "pcb4xhJVbkymetw2IfPsaifZiDVvYK3DSNk4O5vJlPuS3D1OV3QMjLyaMCqNKR7ORgN7a1PN1g" \
  "RGnh774dChsVOIfEmmzBO9bi93bSPdOf5LvuW2Xh5koiOQkwxY7ikU+"                    \
  "fLM23WfHT8OmcrtJ1mBOYZcC3n7hqchrz7Q0jL3xx8f/XAoJs+tZCbZneftfCU+/"           \
  "rLMmIkfZjyAMSDzcnMJ3kgwZNCY6FjmdsiIjPU2ZasgWSRKFYMmuZoiH5g+"                \
  "enRujvk4cLmcnsdd+8qV5LGBSGRFzsWiwhkfmS+"                                    \
  "TH4f8F8FU7CmbzdofZod308k3h6q9ofqOBLIRleQ/"                                  \
  "Tp062jI39zewUaw7BOflzwAAAABJRU5ErkJggg=="
#define ZEND_LOGO_DATA_URI                                                     \
  "data:image/"                                                                \
  "png;base64,"                                                                \
  "iVBORw0KGgoAAAANSUhEUgAAAPoAAAAvCAYAAADKH9ehAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZS" \
  "BJbWFnZVJlYWR5ccllPAAAEWJJREFUeNrsXQl0VNUZvjNJSAgEAxHCGsNitSBFxB1l0boUW1pp" \
  "3VAUrKLWKgUPUlEB13K0Yq1alaXWuh5EadWK1F0s1gJaoaCgQDRKBBJDVhKSzPR+"           \
  "zPfg5vLevCUzmZnwvnP+k8ybN3fevfff73/vBAJTHxc+khL5kr6T1ODk5nAgTRTWloghFVtEg/" \
  "zfh2PkSvq9pJGSKiX9SdKittbJoD/PSYkrJD0vKeB4IsNNotfuUtHk/"                    \
  "CM+IvijpF9KGiDpGEkLJZ3lC7qPeKKTpD9IWiDpUOfWPCi61ZeLvD2VIhTwp9QlTjK5NsIXdB/" \
  "xxHmSpvD/OucWPSAyQw2+LfeG1SbXVra1Tqb785xUaNdMel0g7Iu5V1zPv6dJqpD0kKR/"      \
  "+ILuI55o8oeg1bFT0kWSOkraQxK+oPvw0TZR3ZY758foyQXf//ZxUFh0Q/"                 \
  "GEfNf9gHkaJ6m7pHJJSyTt9tnXhxtBR2EGlnHCMbZMaHuHzX19JZ0u6VRJh0k6hM+"          \
  "BpMjnklZIelPSNhff3V5StkNlEWBMFm+3LcC+BW3GuZP2GvfmiEiCCMUzxZIKRGSt9zeML/"    \
  "fdGAW9JB3O8c6SlMZ+b5f0qaQiF7EpnieXY1auvZfG7zhSUk8RSS428F7M5xfsh1eAV/"       \
  "vxOzoq16sklZBqbdpo5H2qDPRQXoP3Ki0+20FSFyrZUgt+Rt/7KH2vZb8/t/iMG2Sy/"        \
  "0dI6sbvgHGoV8a3xErQb5Q0iTfHCplkzlkW7w+VNF3ST7QJUzFK0pVkDFiw+"               \
  "yV95uC7r5Z0k3CW2ApwIkrJ9B9IelfSh2SIlqC/"                                    \
  "pDFUZAVk0rQoMhk2GYswx+"                                                     \
  "AtWvMKPtcyEckW37pPwsIHNAuBniDpYhEpBMmJwvibJL0gIlVh39r0C8UlczkXQ/"           \
  "mM6OtEzuf3RfPVAxUY47f5PStcGKPxpOMldbbxiBptPMavJX1PuQ/P/"                    \
  "olyz12S7rD4PLyqBTQ8gyXVSOot6VK+dxR53wyl7POjkv7pkpcwpleJSCHP4eQjM0BB/"       \
  "ZuG4Hl9EO8mQx4ZQ0FfL+k+k+t4wNlULpkO24IGnSzpQklzKPDRAMvZ1eXz9uXfH/"          \
  "Pvx5Ie44C5zYQXUgDPj6LEnMCQ3AFkjjupjGF9/"                                    \
  "kJmxPw1oiquz+6dalXcCRSmYxwK0kDSRI71azb3Y+6GiMi6P/"                          \
  "5ey3F3YpExjxdQoG61uX8gBetkh2OWFkUIVGUT1pS9yosZNu1nkl8uZH+"                  \
  "mikhxkx1wz7mkB0WkXsKJFw1ZuSWKotY9wjNJS6mUy41JK5P0c2qCnBgIeQWZvEK7Dnf6WUljT" \
  "T5TS7d0KwezkJShdWIeGeuKKJo7FktUQylcl0i6RtL/"                                \
  "HH4OjP+wB0UTLTGHfubRDWyi1g7SaoZQ495z9w7RpaHKqHEfLeklEyWzk+7dl3TTu1KQCpV7+"  \
  "pBB4IWstFFAgvOpJnTL6DoW0xPbw3k/"                                            \
  "nIYkW+kbmHeXhUEABklazrBDBdzTDfyuBo5DPq1eoUk7ZbSk70l6n3MZjUdCDpQvMF/rezn7/"  \
  "hX7Xs8wsj/"                                                                 \
  "7rsrWdQxnZtrwwENUosJkDDZxTjOUkEH1ds6lzJyDZzGScRsonGNcMCIG+"                 \
  "WgRKTRQ8Su2p7uRi/"                                                          \
  "mlKjZKekREChS2KIOcTvfqp3RZDlM+"                                             \
  "cxnfv8Thc75Pt8kqo92VzNTbxBqcQlceivAdByHDIxbvFTMOLovyHAGGK3qc/"              \
  "jJDoDc4hpjABzBm4UAglBFqEAOqt8mB29ss4uJnNCHfSK/"                             \
  "tVZMYEfMykt7Bcco1eDLDHCT8gmzzRdLHZL6wRSgzg6GIgVl8Xj2uhPA+"                  \
  "oQn53yTdK2mVMC8NzuJ8zaSyM/ApxyzWCFJRvUQ3eQ29BTNFcRgt+FTl2g30zDZZtD/"        \
  "ZRMifE5ES6Y9MxqAHQ7XZikI9nd97j5p1f83GZTPr6Crt2sOcOB1zTYT8HrqjVRZx4wbSAt47S" \
  "Xn/YsZV9zp4zuvJgNGQRaszmoN1rBY6IH4dHiVHcA5dZd2zeIbPv8ZBkghYTQFTx/"          \
  "h1WvSz6c3kM5ewGG8Prvxc5DZWS2u+dypnM5Y3sIJMXmbxfXW0misZN56oxITnWsyl2fg+6+C+" \
  "zWTefMWr68RwaYF271htHBZqCsKqL28wB/"                                         \
  "ACjYShrE9nUjfWmEU33A7woqbR4k5UlNk4yoYOzOHvtGs30KO1QgnlZC2VohGOIGn7WEvW0Zdo" \
  "MeCHfBgdo8X++m3V+s2wEHKzJMblJom92+"                                         \
  "ne2SHDwT1gknUispPpJLrrVZqwLxTmy5F5jOdVS72F/b6UwlbrcEytrD00+a8l/"            \
  "ZUM82jEZd8peu8uNYS8JxNWqis5IYqQCy1rPUULh8Y7fOYal3zzmPb6aJN7zlf+"            \
  "32bBV9ESclNE85WUX4j4oNbl/fM1b2eoxX3jyXNqiDTP4Xe8Rm9ItfSjvAr6DM0d+o5MXW/"    \
  "CuHO0a7eZTLYT3KF9LktYZ/"                                                    \
  "WdCI+IkoV+lFZ6l3J9OF14HdM0F3MrhXxFjJmqhh5FBera24XqxaCqL0UosK97Z2ku+"        \
  "yJaEqf4D62ByoROcjZuN78Xaa9zTBSzKvxvC+vlrmgWVPU2h4j4FCO5lZ+vNBnpYHHfOOX/"    \
  "PfR83eApTaGM8CLop5l88WSLWAOu4AiNme5owcBO1xhlLGO/eGAFkyYqrtFe5zKzqU7KBE5o/"  \
  "BAIiv7VJSK7qV4GhEF1XtSk0YseWl6lWYI+cXj6pigJLkH3Vk0qfebxe4q0JGOGSDxCWn/"     \
  "Nchk9qJgMfGKS87LDes1IHeVW0LszgaC6sPMYE5lBt4CzRcuy4lVMLKlWfWwcJ+"            \
  "YpxtcGjtOYfzRjTgNIlv0rnpyCveeHNFSJ/jUlonH/"                                 \
  "3nNYqyOU28qYhHOLbzVPqFc81JQDKxnQ5twLdmjfmQzlxU6eoZ/"                        \
  "mma3y8D3VonlhUr6bElhMwJ81RseSxW+jfOYULdYGAw5s4WBtpeU0ijKwxnp/"              \
  "HCfn70piCNlMFEUU8/WpmnZe1Bq80r96m5yMkIwx9nnNHTWFs114q0ArM1HsiUY7j5/"        \
  "rKFIThdrrzR7agHyoy9vd3Ag64uEfKa+xjIKlLqtTUBB7FWgJrQ9joFl1d2cQ2wzHaeDXa6/"   \
  "ztO9Wx+OT+FrzSAKuV12ptOZp+"                                                 \
  "ljnaVawk8uxDpnMZXYCGB3PXqe5sl7QQ5ubhhQR9B4mQpvjIR+gJgrbOxV0rK/"             \
  "rVUyXmyRWdI2a2YLEhVP3BwmN9sJ9BtQpKkxiSDOrUeUhaeQaPevKzKQ3oIVTSGatcynoRl29s" \
  "Ikh440a8pURNoz00Ab4Ts1obxCps1FKl8k5IpKbcmsgu6nz6ETQC+"                      \
  "iSqoKKOPmVJBmYnDjHX4EozB9s7TgwykkyYS13URAHpmstYIloOP/"                      \
  "HEi6Wx5a4+DwSpH2V18tTyHUPm3iQeS1s09ai4/"                                    \
  "0ntVgNRQmzHTRulGwaQNnei3FgHqPcMBEJlXrNioAaE8AcupKBd7ElBu1uTxCzg+"           \
  "dmKB4TahiQNX/"                                                              \
  "OxssAb00Uzdeci4S3FYhEQdfkWCrc1cI2K+"                                        \
  "2EDhsP1OUxZGUnOWTmcgphV0UgZ4jUR1hLlBiuJfqJpb61CXimOrq8RqiEeu6TU3iMwdzYgWhU" \
  "nWHDDKr0ptLar6USqmOfYYiGMMTUN/"                                             \
  "KgziGVTo+pNJHBBfF0zVAQc6N2DUL+tcO2Yc1Rk2ss+"                                \
  "yBmOko43yCSCljJXAWA7PD4eAt6MBy2yiNACRvVVN05t40pPLYPsT+zlRDpOLG/"            \
  "Jt8OSGKhmnBpivV7q/"                                                         \
  "Y6JkucVgkyWKb52rVZwl0tvNDi+"                                                \
  "AzRvKjfK1Dnjvpd1FhPEc1LBVsbqENXN35cFaPY2BIVGdlWYZKqgPPj/"                   \
  "RythNtpcNycpoOxwAae0bGwhAkAQg01cfiDWDRqZtHhCqFQ5FAtOXKXh/"                  \
  "Yh6Ci2N5YMUDW2SHg/"                                                         \
  "N3scn02N++cnMIZCBdwS9gtApRxqDc6OlzWtSrdc8cJGlzP5fzZDri1tQNixISWL/"          \
  "5fSQvcVzfe/wzXfSG8Kuw03pHB/t5KMik+EYJ1EC1d0zCw6fofqRI2ZJwpvyxN4uPs0q/"      \
  "6UR2szyESobxatf3aa7jvfrT0DGPNpYV3H3CI0BYLGllQdy7TX14rUP/"                   \
  "zzDHpuRp0EPLnJvH68Qij/"                                                     \
  "RXnyIyku5Ea+5S3NO7s01q77eMY1qqY8T7Qs+4qtq+"                                 \
  "o2UWhjZO6HuWhjJBlZXWbAHvbFSTAxqMW+RbuG3VfviAP36tshujINh6Tr3kE0BNMl5x8Qq6+"  \
  "mVTdwrMlzpRrGaGPzVpw9NDNFngjoFZZzRCS/FRPXHRZT31X2MgfYTQYX1WE1moaaQJfKEFTs/" \
  "camkXnUwt9YtNWPiuc67VmRlb0yiRgS/"                                           \
  "cAe7is0QXuTAm9kikM2DNc5OkeGRaMU8tq0TJHbUCOtezMeRfITiSv1PLLbGE5gb/NOB/"      \
  "1AuR1KlLETDltidyR4XIPasyEnc6eIbRa9kfNifFeXJOAnVJBiKfFCvobcLKccLHWojHJpIPH3" \
  "iXQlpoNLrdcH44sucvmQOHHjZ9rDrGdbixVmbk/"                                    \
  "XGy4mtiKuoQDjmQpFJLs6wuSZvqKmL0ky6zOZLry+420UKUaue5ooyeqy9+"                \
  "iopgM989cp1Dcp16bSU1tOJbyFyjedTID5wOk6OAUFFXUDKFRLkmBM3xH7fzIJwPLsxexDMWP2" \
  "b8g38DqN45ywCuH0VNuv+"                                                      \
  "XmjwOYCjtUakbg6AkGlNoQGBMB5A9g8hh2g7zFE2U4F35FxfHfmwwbxcz3Yl32C/"           \
  "oAwPwDAS6UXdpOhXPZ27Trc9R/SLTla0zzGoXl2QAexnLVZJB/"                         \
  "CZMpV7HthfL4lJIrb54u+tdv3/"                                                 \
  "rCiSbw+k88yM9ZxXgKwlHmZycq13iSr0KeMHmUZw6r1VICrLT4D5fy4wq/"                 \
  "5DAvfjaWC9oAd9KxwTNUJynUjL+EqpwSTME1zOWMBuIxmZ7p9RCsNq+"                    \
  "NmdxW09I1MdNkJeYZNHsIt0qKEO2Z4kvmHadS+"                                     \
  "Xqv2cqzc93rpuhdl54tg2DISuJljBW3uZjMHrAPqHOYK6zPIM23G2+"                     \
  "14Rts4cyLbdxo3Y667UskOo/W/m/"                                               \
  "PwRhQBwZFkT2vXzDbTtLMZCyfP1155bbfDrpjKZoYH41bO+"                            \
  "d97jmEgMPVxFMF0iHESIkiNtDhKuwV058cw0dBZNP+lFsSU/6VWf0E4P/x+IF2eJnokr4uW/"   \
  "2jAKPYjjRb7Cxef70c3qsCl0im1Gj/"                                             \
  "Uu2eF6sWo0rUiTQq7zS+"                                                       \
  "pYjywnXYwcyOZfI4mKgHj9N2ttHqbRfSlQXhjw5XXy4S7ZbzOovkxVRsphHp8ia3HlyleZS1zH" \
  "cvoVrdjuNFdEe7edGHzSbpSria/WZ3+cxYV5DCx/4w7FUfyfTW0WO+i7x2YrzKUXZFw/"       \
  "sut+OxJDGkHUxEZPwgCquQcIgxZR9oXekDQk8FF60bqwocupaIoEz6EmaC3C+"              \
  "0Ro6Wgp4eb2tpPJqN+"                                                         \
  "4xXFXQ3TfUfCc5PDNnLZDpLIV1NADKyjZa87mHgmWX57bYdIfIY3pdCGf43xQUXI62kBn3fZxi" \
  "4SPC8crIjDQ4yzFAaz/XcPJn7xf03VRzIB5Z7qCbBzPQi5jga2E9bCD+ELug8ficEZCk/"      \
  "Cmj8Ro3aLtLxDR1/"                                                           \
  "QffhIHNRTUZCf+S5G7SJBp2b7G31B9+EjcVAFEInZQ2LU7jiN1zf4gu7DR+"                \
  "KwTvkfO9bGx6BNnEQ8XXmN5cT3fEH34SNxwN4A9dgknIEwyWNbeRTwV7WYHBVwFQfbwKb7vOUj" \
  "iYAiKVT1PczXqCLD/n5UbuLcNxTKoCgExSFNmsFCHI6iJBQFnUbqqbWPHyFceDAOrC/"        \
  "oPpIN+FVaVLrNUa6dLPbvoEQdO4pd1OUylBVkCutsOkqosbNvwcE6qL6g+"                 \
  "0hG3MY4ejots1pT3kE4P9QDdfuLKeDfHswD6gu6j2TF2yQcLoqEGurre9EdP1QTfmxJRdn0Nlr" \
  "vD+jmY69Egz+UQvxfgAEALJ4EcRDa/toAAAAASUVORK5CYII="

BEGIN_EXTERN_C()
PHP_FUNCTION(phpversion);
PHP_FUNCTION(phpinfo);
PHP_FUNCTION(phpcredits);
PHP_FUNCTION(php_sapi_name);
PHP_FUNCTION(php_uname);
PHP_FUNCTION(php_ini_scanned_files);
PHP_FUNCTION(php_ini_loaded_file);
PHPAPI zend_string *php_info_html_esc(char *string);
PHPAPI void php_info_html_esc_write(char *string, int str_len);
PHPAPI void php_print_info_htmlhead(void);
PHPAPI void php_print_info(int flag);
PHPAPI void php_print_style(void);
PHPAPI void php_info_print_style(void);
PHPAPI void php_info_print_table_colspan_header(int num_cols, char *header);
PHPAPI void php_info_print_table_header(int num_cols, ...);
PHPAPI void php_info_print_table_row(int num_cols, ...);
PHPAPI void php_info_print_table_row_ex(int num_cols, const char *, ...);
PHPAPI void php_info_print_table_start(void);
PHPAPI void php_info_print_table_end(void);
PHPAPI void php_info_print_box_start(int bg);
PHPAPI void php_info_print_box_end(void);
PHPAPI void php_info_print_hr(void);
PHPAPI void php_info_print_module(zend_module_entry *module);
PHPAPI zend_string *php_get_uname(char mode);

void register_phpinfo_constants(INIT_FUNC_ARGS);
END_EXTERN_C()

#endif /* INFO_H */
