# BITCS������Ŀ������

����Ŀ���ڿ����С�  
Github�洢���ַ��<https://github.com/howmanyKsdoIneed/BITSE-sudoku>

����Ŀ��PSP2.1�������£�

|��Ŀ|Ԥ����ʱ(min)|ʵ�ʺ�ʱ(min)|
|:---|:-:|:-:|
|�ƻ�|120||
|�� ��������ʱ��|120||
|����|1140||
|�� �������/�¼���ѧϰ|240||
|�� ��������ĵ�|120||
|�� ��Ƹ���|60||
|�� ����淶|60||
|�� �������|240||
|�� ����|240||
|�� ���븴��|60||
|�� ����|120||
|����|210||
|�� ���Ա���|120||
|�� ���㹤����|30||
|�� �º��ܽᣬ������̸Ľ��ƻ�|60||
|�ܼ�|1470||

## 1 �������

����Ŀ��������Ҫ�������֣����������վֺͽ�һ���������⡣

�����վֲ��֣�����Ҫ���ɵ��վ�����N(1\<=N\<=1E6)���ڶ�ʱ���ڸ�Ч����N���Ϸ��Ҳ��ظ��������վ֣����浽�ļ��С���Щ�վ����Ͻǵ����ֱ���ȫ����3������Ӧ��ʶ������Ƿ�Ϸ������������쳣�����������

���������֣���������ļ����ж�ȡ������Ŀ����0������λ���������ļ��е�ÿһ�����⣬����������һ�����нⲢ�����ļ���ÿ����Ŀ��λ����30-60��֮�䣬ÿ���Ź���������2����λ���������ݱ�֤��ȷ����Ŀ������1��1E6֮�䡣

## 2 ����˼·����

### �վֵĹ���

���ȿ��������վ����ɲ��֡�����Ҫ�ڶ�ʱ�������ɴ��������վ֣���ֱ�Ӳ��û��ݷ���⣬ÿһ�У����У��Ź��񣩶����һ�����������������Լ��9!^9����1E50���ң�����һ���ⶼ�޷���ʱ���ɡ������ȡĳ�ּ��㷨����ĳ�ַ������졣

����һ���Ѿ�����һ�У�������Ϊ�ǵ�һ�У�������λ�þ�Ϊ��λ������������һ��ѭ������3����6��λ�ú�ֱ������2��3�У����õĽ����ǰ���У����Ѿ��������У��У����б�Ȼ��������Ҫ�󣻲��ѵ�֪�������Ź���Ҳ��������Ҫ��  
��ǰ����ÿ��ѭ������1��2λ������4-6��7-9���С���ǰ�����ƣ�ÿһ�б�Ȼ��������Ҫ��5��6�пɿ�����4��ѭ������3��6λ�Ľ�����ʿ�֪ÿ���Ź���Ҳ��������Ҫ��7-9��ͬ����  
ͬ�������ѷ����������ɵ���������ÿһ�еĸ���Ԫ�ظպ�һһ��Ӧ��һ�еĸ���Ԫ�أ���ÿһ��Ҳ����������Ҫ��  
���ϣ�ֻҪȷ���˵�һ�У�������˷�����һ�������վ֡��ڱ��ⱳ���£��Ϸ��ĵ�һ�й���8!=40,320�֡�

����һ���Ϸ��������վ֡�������⽻�����У���Ȼ�����ƻ��С����ϵ������������������ƻ��Ź����ڵ�������������������ͬ�������Ź�����У���4��5��6�ж���Ӧ�ڶ��žŹ��񣩣��Ͳ����ƻ����������ˡ�����ڱ���������£���һλ��Ϊ3��������һ���Ϸ��������վ֣����ɹ����2!\*3!\*3!=72�ֱ��塣�������ַ�����ϣ����Թ����2,903,040�ֲ�ͬ�������վ֡�  
ʵ���ϻ����Խ�4-6��7-9�����彻���������ɹ�����������վ����������ټӱ���

���������㷨ԶԶ���ܹ�������п��ܵ������վ֣����Ѿ���������Ŀ�����Ҫ��

### �վֵı���

������0-2,903,039֮�䣨������������һһ��Ӧ�ر��밴��������������������վ֡������վ����ɵ�һ�еı仯�͸��е����������ֹ�����ɵġ�ǰ����8!=40,320�ֱ仯��������72�ֱ仯����˿ɽ��������72a+b����ʽ������a,b������������a<40,320;b<72��a�����˵�һ����α仯��b������ʣ����������С�

���ȿ���a����һ�е������ֿɿ����ڶ�����ȷ��������λ�õ�ȷ������a/7!���Ե����ڶ�����(��1λ�ϵ���)�ı��롣ͬ���أ�(a mod 7!)/6!���Ե������������ı��룬�������ơ�  
��ˣ���iλ(i=1,2��...,7)�ı���Ϊ(a mod (9-i)!)/(8-i)!����8λ�ı���Ϊ0��ÿ��ȷ���˱���󣬾����Լ��ҷ��ڱ������������e.g. ���ڵ�2λ�ģ�������Ϊ5�������7λ����������������λ���Ƚ������Ҳ��λ�ú󽻻����������빹�����վֵĵ�һ�С�

�����Ƶķ�ʽ����b��b������Ϊb1\*36+b2\*6+b3�����֣�����b1ȡ0��1��b2��b3ȡ0,1��2��0�������Ͻǵ�����Ҫ�����ƶ�����b1=1����ʾӦ����1,2���У����򲻻�����b2%3��ʾ��3�к͵�3+i�л�����b2����ż�Ա�ʾ4,5���Ƿ��ٻ�����6-8��ͬ����

����������һ������Ψһ�ر�ʾ�˹�����������վ֡�

### ���

�������û�������վ������Ĺ��췽����ֻ���ڻ��ݷ��Ļ����ϣ������Ż������ȿ��Գ���ʹ�������������Ż���Ҳ�������˴��������������������ȷ�����ѡ���ֱȽ��ٵĿ�λ����֦����ͬʱ����ĳ�����ֵ�ǰ���ܳ����ڲ�ͬ�Ź�����ĸ�λ���ϣ��Ӷ��������ڲ�����������ȵ�����£���������������Ŀ�λ�����ų��������Ч�⡣

## 3 ��Ƽ���

�����Ϊ����ģ������������������֡������ฺ����ܲ������������Э������ģ�鹤���������ౣ��һ������״̬����ӵ�����¹��ܣ�

1. ��������ֹ�ⲿֱ�ӷ����������̵��ڲ����ݽṹ��ͨ�����ַ�ʽԤ����ӷ��������Ͼ���λ�����ֵķ�����
2. ��Ч�Լ�顣��鵱ǰ������״̬�Ƿ�Ϸ����ɸ������������ָ����λ��Ϊ�Ϸ����ǷǷ���
3. �վ�����ģ�顣�������n(0<=n<=2,903,039)���������������㷨�������n�������վ֡���������ʹ�ظ�ִ�г����������ͬ��Ϊ���ܡ�
4. ������ģ�顣����Ҫ���������Ϳ�ʼ������λ��(���ȳ��������ֵĿ�λ)���ݹ��������������⣨�����ݣ������Ķ�����ͼ�������������⡣���ý⣬����true����ʱ�������ݱ��Ķ���Ϊ�������վ֣���û�еý⣬����false������ԭ��Ŀ���䡣
5. ��������ģ�顣���������ж�һ��������Ŀ�����վ֣������Ϸ��ԡ�
6. �������ģ�顣���������дһ�������վ֣������ؼ��Ϸ��ԡ�

���¾ͼ����ϸ��ӵ�ģ������ϸ���ܡ�

### ����ģ��

���ȶ�����������������Ϸ��ԡ�����ӦΪ��������һ������������-c��-s��  
��Ϊ-c����ڶ������������תΪС�ڵ���100,000������������Ϊ-s����ڶ�������Ӧ��һ�����Դ򿪵��ļ���·����
֮�������������ۣ�

- -c,�����ָ���������վ֡�������ѡ������������0-2,903,039��������������Щ��Ŷ�Ӧ�������վֲ��������ļ���Ҳ�ɴ�0��ʼ��һ���ɡ�
- -s,������������ָ�����ļ���ÿ�ζ���һ��������Ŀ�����ɽ�����ģ����⣬ֱ���ļ�����Ϊֹ����ÿһ��������Ŀ�����ܹ��������������ļ��������ӡ������Ϣ��

### �վ�����ģ��

��������ı�ţ������Ͻ����֣�����ģ���Ŀ���Ǹ�����Ŷ�Ӧ�������վ֡�

������0��ʼ��һ���������棬֮�����ɵ�һ�У��ڵ�һ������1-9�󣬽�1��Ҫ������Ͻ����ֻ������������һ��ÿһλ�ı��롣�ӵڶ�λ��ʼ�����iλ�ı�����k���򻥻���iλ�͵�i+kλ��

���ɵ�һ�к���ǰ��ƽ�Ƶ�һ�еķ����������֮����У����b�ı����֮����н��л������μ��վֵı��벿�֡���󣬷������ɵ������վ֡�

### ������ģ��

�ýϼ򵥵Ļ��ݷ���⡣�㷨������ʾ��

1. �ҿ�ʼ�����Ŀ�λ���������λ�÷Ƿ����ǿ�λ�����������λ�ã��ҳ���һ����λ��Ϊ��ʼ�����Ŀ�λ�����Ҳ�����˵�������Ѿ������ˣ�����true�����򣬼���ִ�С�
2. ������λ�����С��С��Ź��������е����֣��ҳ���ǰ�����кϷ����������֡����Ҳ�����ֱ�ӷ���false��
3. �Կ������ÿһ�����֣���������󣬵ݹ���ñ�������������true����������ҵ��⣬ֱ�ӷ���true��������false�������������һ�����֡��ݲ������ӵ�������������λ�á�
4. ��2��ÿһ���ӵ��ö�����false�������δ�ҵ��Ϸ��⡣�����λ������Ϊ0��������false��