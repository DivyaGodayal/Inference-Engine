# Inference-Engine

After the high-profile lawsuit in which you succeeded to bring RealityMan to justice after proving that distributing his Nintendo emulator was a criminal act, everyone wants to hire you! From disputes over tech patents, to lawsuits on questions of privacy in social media, to suits on liability issues with self-driving cars, to disputes between Hollywood celebrities and their agents or producers, you are just running out of time and energy to run all these cases by hand like we have done in the lectures.

Because of the highly sensitive nature of the cases you handle, and because of the extremely high monetary amounts involved, you cannot trust any existing. You thus decide to create your own, ultra-optimized inference engine.

After much debating, you decide that the knowledge bases which you will create to handle each case will contain sentences with the following defined operators:
NOT X ~X
X OR Y X | Y

**Format for input.txt:**
 <NQ = NUMBER OF QUERIES>
<QUERY 1>
_ _ _ 
<QUERY NQ>
<NS = NUMBER OF GIVEN SENTENCES IN THE KNOWLEDGE BASE>
<SENTENCE 1>
_ _ _
<SENTENCE NS>


**Format for output.txt:**
For each query, determine if that query can be inferred from the knowledge base or not, one query per line:
<ANSWER 1>
_ _ _
<ANSWER NQ>
where
each answer should be either TRUE if you can prove that the corresponding query sentence is true given the knowledge base, or FALSE if you cannot.