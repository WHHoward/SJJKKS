#########################################################################
# File Name: untitled.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: 2022年09月29日 星期四 13时22分26秒
#########################################################################
#!/bin/bash
appname=`basename $0 | sed s,\.sh$,,`
dirname=`dirname $0`
tmp="${dirname#?}"
if [ "${dirname%$tmp}" != "/" ]; then
dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname
export LD_LIBRARY_PATH
$dirname/$appname "$@"
