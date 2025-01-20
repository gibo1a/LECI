function hashCode = hf4(element,nhf)
% USAGE EXAMPLE: hc=hf4('abcd',3)
% input : element  - string 
%         nhf      - number of the hash function to apply (1 to 5)
% output: hashCode - from 1 to 1013 (M)     

% AT, jan 2025

%% configuration parameter. Do not chage
n = 5;  % max number of hash function
M = 1013; % to limit hashcode to M-1
 

%% check if nhf in the correct range
if nhf <1 || nhf > n
    fprintf(1,'ERROR! hf number must be between 1 and %d\n',n);
    hashCode = -1;
    return
end




R =[   79080       13772       68531       47539       72921
       87919       40938        3090       43250       24761
       12326       88885       26879       62734       49110
       88656       76895        4482       68854       67855
       61379       93132        9428       73253       86474
        9468       63649       79928       26792       93112
       27032        3467       67443       65974       53115
       53082       82420       30779       63586       13456
       92939       90657       92232       15784       14491
       93655       65881        3344       11551       24995
       15299       73549       42586       48373       81603
       94209       72131       37036       93156       24682
       92906       38071       74304       33039       79037
       47113       63623       77185       56808       23638
       77678       16616       18139       21724       90198
       ]';

l = 9;  %    

%% use only l chars. Pad with spaces if  shorter than l
kept = element;
if length(element) < l
    desired_length = l;   
    element = sprintf('%-*s', desired_length, element);   
else
    element = element(1:l); % keep only 1st l chars
end


R=R(:,1:l);
 
% each line of R defines a different hash function
r=R(nhf,:);

%   (\sum r * x ) mode M
hashCode=mod(sum (r.*  double(element)),M)+1;

% uncomment to see results during debugging 
%fprintf("%s -> %d\n",element,hashCode)



