import re

START_PATTERN = r'(\/\/atomic_init)'
END_PATTERN = r'\/\/atomic_end'
FUNC_PATTERN = pattern = r'(\w+)\s+(\w+)\((.*?)\)\s*{((?:[^{}]*|{(?:[^{}]*|{[^{}]*})*})*)}'
pattern = r"\/\/atomic_init(.*?)\/\/atomic_end"
header_pat = r'#include\s+(<[^>]+>|"[^"]+")'
threat__start_pat = r'.*?\bthread\b.*?\n'
threat__end_pat = r'.*?\bjoin\(\).*?\n'
entity_identification_pat = r'(\w+)\* (\w+) = new (\w+);'
assertion_pat = r'^\s*\/\/\s*--(.*)'
assertion_pat_dyn = r'^\s*assert.*$'
event_pat = r'\b(?:bool|int)\s*__event__.*'
assert_variable = r'\b(?:bool|int)\s*__assertion__.*'
# formalcommentstrip = r'(^\s*\/\/__assertion__(.*))';
dropslash = r'//__'
# pat_atomic_init = r'^\s*\/\/atomic_init';
pat_atomic_init = r'(.*\/\/.*)'
pat_atomic_end = r'^\s*\/\/atomic_end'
dropslash_assertion = r'//--'
wait_pat = r'.*(wait__\(.*?\);)'
waitconditionpattern = r'\((.*?)\)'
whilepattern = r'while\s*\((.*?)\)\s*{([\s\S]*?)}'

re_pat_atom_init = re.compile(START_PATTERN)
re_pat_atom_end = re.compile(END_PATTERN)
re_pat_function_dec = re.compile(FUNC_PATTERN)
re_pat_threat_start = re.compile(threat__start_pat)
re_pat_threat_end = re.compile(threat__end_pat)
re_entity_identification_pat = re.compile(entity_identification_pat)
re_dropslash = re.compile(dropslash)
re_pat_atomic_init = re.compile(pat_atomic_init)
re_pat_atomic_end = re.compile(pat_atomic_end)
re_dropslash_assertion = re.compile(dropslash_assertion)
re_wait_pat = re.compile(wait_pat)