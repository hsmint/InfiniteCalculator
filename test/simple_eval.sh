echo -e "12*5" > input
./inf_calc input | grep '60' &> result_test1
if [ $? == 0 ]; then
  echo "[TEST 1] OK"
fi
