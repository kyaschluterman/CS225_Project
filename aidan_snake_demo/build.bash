pwd
cd /home/kyasc/Storage/git_personal/CS225_Project/aidan_snake_demo/

# cp /include/resource_dir.h /src/.
# cp /include/config.h /src/.
# cp /include/Fruit.h /src/.
# cp /include/Snake.h /src/.
# cp /include/Obstacle.h /src/.

rm ./a.out

cp /home/kyasc/Storage/git_personal/CS225_Project/aidan_snake_demo/include/*.h /home/kyasc/Storage/git_personal/CS225_Project/aidan_snake_demo/src/.
g++ /home/kyasc/Storage/git_personal/CS225_Project/aidan_snake_demo/src/main.cpp  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
rm /home/kyasc/Storage/git_personal/CS225_Project/aidan_snake_demo//src/*.h


./a.out
