# !/bin/sh
#PBS -N RJR
#PBS -q course
#PBS -l nodes=10:ppn=8

cd /home/rahuljr/DS295/Outbreak/

make all

for j in 2 4 8 16 32 64
do
    mpirun -np $j ./outbreak_mpi.o
    ./outbreak_seq.o
done

