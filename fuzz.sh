#!/bin/bash
rm -rf "./failed-runs"
mkdir "./failed-runs"

failed=0
for curr in {1..1000000}
do
  ./generator > ./test.smt2
  z3 ./test.smt2 > ./res1 
  ./evaluator -i ./test.smt2 > ./res2 

  if ! cmp -s ./res1 ./res2
  then
    failed=$((failed+1))
    mv ./test.smt2 "./failed-runs/${failed}.smt2"
    mv ./res1 "./failed-runs/${failed}-z3"
    mv ./res2 "./failed-runs/${failed}-evaluator"
  fi

  clear
  echo "Failed ${failed} of ${curr} runs."
  

done
