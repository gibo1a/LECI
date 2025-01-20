classdef MinHash
    methods(Static)
        function v = inicHashFunctions(N, k)
            p = primes(N*2);
            p = p(p >= N);
        
            p = p(randperm(length(p),1)); 
        
            v.p = p;
            v.M = N;
            v.a = randi([1,(p-1)],1,k); 
            v.b = randi([0,(p-1)],1,k);
            
        end
        
        
        function matriz_assinaturas = assinaturas(Sets, v, k)
        
            Nu = length(Sets);
            matriz_assinaturas = zeros(k, Nu);
        
            for i = 1:Nu
                x = Sets{i};
                for j = 1:k
                    matriz_assinaturas(j,i) = min(mod(mod(v.a(j).*x + v.b(j) ,v.p),v.M));
                end
            end
        end
        
        
        function distSign = distanciaAssinatura(Msign, k)
        
            Nu = size(Msign,2);
        
            distSign = zeros(Nu, Nu);
        
            for n1= 1:Nu
                for n2= n1+1:Nu
                    c1 = Msign(:,n1);
                    c2 = Msign(:,n2);
        
                    distSign(n1,n2) = 1 - sum(c1 == c2)/k; 
                end
            end
        end
        
        
        function Sets = createShingles(filmNames, shingle_size)
            %Sets = cell(size(filmNames, 1), 1);
            %Sets = cell(1, 1);
            shingles = [];
            for i = 1:length(filmNames)
                cont = filmNames(i, :);
                %name = cat(2, cont{1, 1}, ' ', cont{1, 2}, ' ', cont{1, 3});
        
                name = ''; 
                for idx = 1:size(cont, 2)
                    name = [name, cont{1, idx}, ' ']; 
                end
                name = strtrim(name);
        
        
                %shingles = [];
                for j = 1:(length(name) - shingle_size + 1)
                    shingles(end + 1) = sum(double(name(j:j + shingle_size - 1))); 
                end
        
                %Sets{i} = unique(shingles);
            end
            %Sets{1} = unique(shingles);
            Sets = unique(shingles);
        end
    end
end