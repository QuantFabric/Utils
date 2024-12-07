#!/bin/bash
ulimit -c unlimited
WORK_PATH=$(cd $(dirname $0); pwd)
LOG_PATH=$WORK_PATH/log
mkdir -p $LOG_PATH
cd $WORK_PATH
nohup $WORK_PATH/consumer consumer1 > $LOG_PATH/consumer1.log 2>&1 &
nohup $WORK_PATH/consumer consumer2 > $LOG_PATH/consumer2.log 2>&1 &
nohup $WORK_PATH/consumer consumer3 > $LOG_PATH/consumer3.log 2>&1 &
nohup $WORK_PATH/consumer consumer4 > $LOG_PATH/consumer4.log 2>&1 &
nohup $WORK_PATH/producer  producer > $LOG_PATH/producer.log 2>&1 &
