Tutorial 10. Zumbador, generador de melodíasArduino
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270
271
272
273
274
275
276
277
278
279
280
281
282
283
284
285
286
287
288
289
290
291
292
293
294
295
296
297
298
299
300
301
302
303
304
305
// Tutorial 10: Zumbador, generador de melodias
 
 
 
// https://gist.github.com/nicksort/4736535 Fuente original del código
 
 
 
const int c = 261;
 
const int d = 294;
 
const int e = 329;
 
const int f = 349;
 
const int g = 391;
 
const int gS = 415;
 
const int a = 440;
 
const int aS = 455;
 
const int b = 466;
 
const int cH = 523;
 
const int cSH = 554;
 
const int dH = 587;
 
const int dSH = 622;
 
const int eH = 659;
 
const int fH = 698;
 
const int fSH = 740;
 
const int gH = 784;
 
const int gSH = 830;
 
const int aH = 880;
 
 
 
const int buzzerPin = 8;
 
const int ledPin1 = 12;
 
const int ledPin2 = 13;
 
 
 
int counter = 0;
 
 
 
void setup()
 
{
 
  //Setup pin modes
 
  pinMode(buzzerPin, OUTPUT);
 
  pinMode(ledPin1, OUTPUT);
 
  pinMode(ledPin2, OUTPUT);
 
}
 
 
 
void loop()
 
{
 
 
 
  //Play first section
 
  firstSection();
 
 
 
  //Play second section
 
  secondSection();
 
 
 
  //Variant 1
 
  beep(f, 250);
 
  beep(gS, 500);
 
  beep(f, 350);
 
  beep(a, 125);
 
  beep(cH, 500);
 
  beep(a, 375);
 
  beep(cH, 125);
 
  beep(eH, 650);
 
 
 
  delay(500);
 
 
 
  //Repeat second section
 
  secondSection();
 
 
 
  //Variant 2
 
  beep(f, 250);
 
  beep(gS, 500);
 
  beep(f, 375);
 
  beep(cH, 125);
 
  beep(a, 500);
 
  beep(f, 375);
 
  beep(cH, 125);
 
  beep(a, 650);
 
 
 
  delay(650);
 
}
 
 
 
void beep(int note, int duration)
 
{
 
  //Play tone on buzzerPin
 
  tone(buzzerPin, note, duration);
 
 
 
  //Play different LED depending on value of 'counter'
 
  if(counter % 2 == 0)
 
  {
 
    digitalWrite(ledPin1, HIGH);
 
    delay(duration);
 
    digitalWrite(ledPin1, LOW);
 
  }else
 
  {
 
    digitalWrite(ledPin2, HIGH);
 
    delay(duration);
 
    digitalWrite(ledPin2, LOW);
 
  }
 
 
 
  //Stop tone on buzzerPin
 
  noTone(buzzerPin);
 
 
 
  delay(50);
 
 
 
  //Increment counter
 
  counter++;
 
}
 
 
 
void firstSection()
 
{
 
  beep(a, 500);
 
  beep(a, 500);
 
  beep(a, 500);
 
  beep(f, 350);
 
  beep(cH, 150);
 
  beep(a, 500);
 
  beep(f, 350);
 
  beep(cH, 150);
 
  beep(a, 650);
 
 
 
  delay(500);
 
 
 
  beep(eH, 500);
 
  beep(eH, 500);
 
  beep(eH, 500);
 
  beep(fH, 350);
 
  beep(cH, 150);
 
  beep(gS, 500);
 
  beep(f, 350);
 
  beep(cH, 150);
 
  beep(a, 650);
 
 
 
  delay(500);
 
}
 
 
 
void secondSection()
 
{
 
  beep(aH, 500);
 
  beep(a, 300);
 
  beep(a, 150);
 
  beep(aH, 500);
 
  beep(gSH, 325);
 
  beep(gH, 175);
 
  beep(fSH, 125);
 
  beep(fH, 125);
 
  beep(fSH, 250);
 
 
 
  delay(325);
 
 
 
  beep(aS, 250);
 
  beep(dSH, 500);
 
  beep(dH, 325);
 
  beep(cSH, 175);
 
  beep(cH, 125);
 
  beep(b, 125);
 
  beep(cH, 250);
 
 
 
  delay(350);
 
}
