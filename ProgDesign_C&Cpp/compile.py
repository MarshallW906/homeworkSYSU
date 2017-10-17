
import os
import lorun
import json
import codecs

path = "./all"
test_data_path = "./script/data.json"

def judge_one(input_data, output_data, path):
    
    main_exe = [path, ]

    runcfg = {
        'args': main_exe,
        'fd_in': input_data.fileno(),
        'fd_out': output_data.fileno(),
        'timelimit': 1000,
        'memorylimit': 32000,
    }

    rst = lorun.run(runcfg)
    
    return rst

def judge_main(path):
    f = file(test_data_path)
    test_cases = json.load(f)
    i = 0
    grade = 0
    timeuse = 0
    memuse = 0
    count = 0
    correct_count = 0
    report = "Running Question Test\n"
    for each_case in test_cases:
        i += 1
        test_input = each_case["input"]
        ##test_output = each_case["output"]
        f_input = codecs.open("temp/input.txt", "w")
        f_input.write(test_input)
        f_input.close()

        input_data = file("temp/input.txt")
        output_data = file("temp/output.txt", "w")

        rst = judge_one(input_data, output_data, path)
        if rst == False:
            report += "(%spts) Fail Case %s: System Error\n" % (str(each_case["score"]), str(i))
        elif rst['result'] == 5:
            report += "(%spts) Fail Case %s: Runtime Error\n" % (str(each_case["score"]), str(i))
        elif rst['result'] == 2:
            report += "(%spts) Fail Case %s: Time Limit Exceeded\n" % (str(each_case["score"]), str(i))
        elif rst['result'] == 3:
            report += "(%spts) Fail Case %s: Memory Limit Exceeded\n" % (str(each_case["score"]), str(i))
        else:
            answer = file("temp/output.txt").read()
            correct = each_case["output"]
            correct = correct.replace('\r', '')
            p_answer = answer.replace('\n', '').replace(" ", "")
            p_correct = correct.replace('\n', '').replace(" ", "")

            if correct == answer:
                report += "(%spts) Pass Case %s\n" % (str(each_case["score"]), str(i))
                grade += int(each_case["score"])
                correct_count += 1
            elif p_correct == p_answer:
                report += "(%spts) Pass Case %s: But Presentation Error\n" % (str(each_case["score"]), str(i))
                grade += int(each_case["score"])
                correct_count += 1
            else:
                report += "(%spts) Fail Case %s: Wrong Answer\n" % (str(each_case["score"]), str(i))
            if rst["timeused"]:
                 timeuse += rst["timeused"]
            else:
                 timeuse += 0

            if rst["memoryused"]:
                 memuse += rst["memoryused"]
            else:
                    memuse += 0

            count+=1

    if count != 0:
        timeuse = timeuse / count
        memuse = memuse / count
    else:
        imeuse = memuse = 0
    
    report += "Total: %s of %s test cases passed\n" % (str(correct_count), str(i))

    return (report, grade)

def run():
    for each in os.listdir(path):

        bubble_sort_program = os.path.join(path, each, "src", "Bubble")
        insertion_sort_program = os.path.join(path, each, "src", "Insertion")
        selection_sort_program = os.path.join(path, each, "src", "Selection")

        f = open(os.path.join("report", each + ".html"), "w")

        f.write("<h1>Report for %s </h1>" % each)
        print each, "\t",

        if os.path.exists(bubble_sort_program):
            report, grade = judge_main(bubble_sort_program)
            
            f.write("<h2>bubble sort</h2><pre>")
            f.write(report)
            f.write("</pre><br>")
            print grade,

        print "\t",

        if os.path.exists(insertion_sort_program):
            report, grade = judge_main(insertion_sort_program)
            f.write("<h2>insertion sort</h2><pre>")
            f.write(report)
            f.write("</pre><br>")
            print grade,

        print "\t",

        if os.path.exists(selection_sort_program):
            report, grade = judge_main(selection_sort_program)
            f.write("<h2>selection sort</h2><pre>")
            f.write(report)
            f.write("</pre><br>")
            print grade,

        f.close()

        print ""


def compile():
    for each in os.listdir(path):
        bubble_sort_file = os.path.join(path, each, "src","Bubble.c")
        bubble_sort_program = os.path.join(path, each, "src", "Bubble")
        insertion_sort_file = os.path.join(path, each, "src","Insertion.c")
        insertion_sort_program = os.path.join(path, each, "src", "Insertion")
        selection_sort_file = os.path.join(path, each, "src", "Selection.c")
        selection_sort_program = os.path.join(path, each, "src", "Selection")
        os.system("gcc %s -o %s" % (bubble_sort_file, bubble_sort_program))
        os.system("gcc %s -o %s" % (insertion_sort_file, insertion_sort_program))
        os.system("gcc %s -o %s" % (selection_sort_file, selection_sort_program))


def main():
    compile()
    run()

if __name__ == '__main__':
    main()