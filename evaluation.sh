echo -e "100+200*300-93" > input
./inf_calc input | grep '60007' &> result_test1
if [ $? == 0 ]; then
  echo "[TEST 1] OK"
fi

echo -e "23-(-34)*40+25" > input
./inf_calc input | grep '1408' &> result_test2
if [ $? == 0 ]; then
  echo "[TEST 2] OK"
fi


echo -e "233423541354.143543524352+2342314123413.34523453*321341241.12341234" > input
./inf_calc input | grep '752682127751965521964.9395178755481002' &> result_test3
if [ $? == 0 ]; then
  echo "[TEST 3] OK"
fi
