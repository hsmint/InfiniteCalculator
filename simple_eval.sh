echo -e "5*30" > input
./inf_calc input | grep '150' &> /dev/null
if [ $? == 0 ]; then
  echo "[TEST 1] OK"
fi
