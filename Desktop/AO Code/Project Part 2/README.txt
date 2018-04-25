To run test_decision_p2.py when running the code it will propt the user to enter the name of the 
test file. If you want to use the trainerP2.txt you dont need to modify the python code, since it is 
already optimized for that test. If you want to run the my_train_data file you need to modify the code. 
the input looks just like this

my_train_data_simplified2.csv

Comment this out:
if line[11] != '':
        line[11] = line[11][0]
    price = round(float(line[10]))
    if price < 10:
        line[10] = "price < 10"
    elif price < 30:
        line[10] = "10< price <30"
    elif price < 60:
        line[10] = "30< price <60"
    elif price < 100:
        line[10] = "60< price <100"
    else:
        line[10] = "100 < price"
    line.pop(9)
    if line[6] != '':
        age = round(float(line[6]))
        if age < 4:
            line[6] = "age < 4"
        elif age < 10:
            line[6] = "4 < age < 10"
        elif age < 18:
            line[6] = "10 < age < 18"
        elif age < 25:
            line[6] = "18 < age < 25"
        elif age < 35:
            line[6] = "25 < age < 35"
        elif age < 50:
            line[6] = "35 < age < 50"
        elif age < 65:
            line[6] = "50 < age < 65"
        else:
            line[6] = "65 < age"
    line.pop(4)
    line.pop(3)
    line.pop(0)
    line.append(line.pop(0))
    
Uncomment this:
"""if int(line[2]) < 75:
        line[2] = "< 75"
    else:
        line[2] = ">=75" """
        
The cod will print out the decision tree. I recommend using the second test file only because the decision tree
looks better.