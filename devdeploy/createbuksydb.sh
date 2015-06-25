sudo ./createdb.sh buksydb buksydba buksy
if [ $? -eq 0 ]; then
    echo Buksy mysql database successfully created!
else
    echo Fail to create buksy mysql database!
fi
