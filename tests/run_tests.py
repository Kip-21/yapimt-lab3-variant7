import json
import random
import subprocess
from pathlib import Path

root = Path(__file__).resolve().parents[1]
exe = root / 'code/build/lab3.exe'
cases = [
    ('empty', ''), ('one', 'a'), ('two', 'ab'), ('three', 'abc'),
    ('four', 'abcd'), ('palindrome', 'aba'), ('repeated', 'aaaa'),
    ('space_inside', 'a b'), ('edge_spaces', ' a '), ('mixed', 'Ab1!'),
    ('russian', 'тест'), ('russian_spaces', 'а роза'),
    ('maximum', 'abc' * 85), ('too_long_256', 'a' * 256),
    ('too_long_300', 'b' * 300), ('one_space', ' '),
    ('three_spaces', '   '),
]
prompt = b'Enter a string (max 255 characters): '
results = []

def check(name, value):
    run = subprocess.run([str(exe)], input=(value + '\r\n').encode('cp866'),
                         capture_output=True, timeout=5)
    if len(value) <= 255:
        expected = prompt + ('Palindrome: ' + value + value[::-1] + '\r\n').encode('cp866')
        passed = run.returncode == 0 and run.stdout == expected and not run.stderr
    else:
        expected_error = b'Error: string is longer than 255 characters.\r\n'
        passed = run.returncode == 1 and run.stdout == prompt and run.stderr == expected_error
    result = {'name': name, 'input': value, 'exit_code': run.returncode,
              'stdout': run.stdout.decode('cp866'), 'stderr': run.stderr.decode('cp866'),
              'passed': passed}
    results.append(result)
    assert passed, result

for name, value in cases:
    check(name, value)

run = subprocess.run([str(exe)], input=b'', capture_output=True, timeout=5)
passed = (run.returncode == 1 and run.stdout == prompt
          and run.stderr == b'Error: input failed.\r\n')
results.append({'name': 'end_of_input', 'exit_code': run.returncode, 'passed': passed})
assert passed

rng = random.Random(7)
alphabet = 'abcXYZ019 !?.,_-тестАБВё'
for length in range(256):
    check(f'length_{length}', ''.join(rng.choice(alphabet) for _ in range(length)))

(root / 'tests/results.json').write_text(
    json.dumps(results, ensure_ascii=False, indent=2), encoding='utf-8')
print(f'Passed {len(results)}/{len(results)} program tests.')
for index in [0, 4, 7, 10, 12, 13, 15, 16]:
    item = results[index]
    print(f'{item["name"]}: exit={item["exit_code"]}, passed={item["passed"]}')
