classdef BloomFilter
    methods(Static)
        % From: https://www.mathworks.com/matlabcentral/fileexchange/27940-string2hash
        function hash = string2hash(str,type)
            switch(type)
                case 'djb2'
                    hash = 5381*ones(size(str,1),1); 
                    for i=1:size(str,2) 
                        hash = mod(hash * 33 + str(:,i), 2^32-1); 
                    end
                case 'sdbm'
                    hash = zeros(size(str,1),1);
                    for i=1:size(str,2) 
                        hash = mod(hash * 65599 + str(:,i), 2^32-1);
                    end
                otherwise
                    error('string_hash:inputs','unknown type');
            end
        end
        
        
        % From: http://willwhim.wpengine.com/2011/09/03/producing-n-hash-functions-by-hashing-only-once/
        function hash_codes = super_hash_codes(str, is)
            hash1 = string2hash(str, 'djb2');
            hash2 = string2hash(str, 'sdbm');
            hash_codes = hash1 + hash2 * is;
        end
        
        
        function result = cal_hash_codes(k, keys)
        
            result = zeros(k, length(keys));
            for i = 1:length(keys)
                key = keys{i};
                hash_codes = BloomFilter.super_hash_codes(key, 1:k);
                for j = 1:k
                    result(j, i) = hash_codes(j);
                end
            end
        end
        
        
        function filter = bloom_filter(n, hash_codes)
        
            filter = zeros(1, n);
        
            for i = 1:size(hash_codes, 2)
                for j = 1:size(hash_codes, 1)
                    hash = hash_codes(j, i);
                    idx = mod(hash, n) + 1;
                    filter(idx) = 1;
                end
            end
        end
        
        
        function filter = bloom_filter_insert(filter, key, k)
            
            hash_codes = BloomFilter.super_hash_codes(key, 1:k);
            
            for i = 1:k
                index = mod(hash_codes(i), length(filter)) + 1;
                filter(index) = 1;
            end
        
        end
        
        
        function ret_val = bloom_filter_maybe_in(filter, key, k)
            
            hash_codes = BloomFilter.super_hash_codes(key, 1:k);
            ret_val = 1;
        
            for i = 1:k
                index = mod(hash_codes(i), length(filter)) + 1;
                ret_val = ret_val & filter(index);
            end
        end
        
        
        function chaves = dataset_init(data)
        
            chaves = cell(size(data, 1), 1);
        
            for i = 1:size(data, 1)
                chaves{i} = cat(2, data{i, 1}, ' ', data{i, 2}, ' ', data{i, 3});
            end
            
            chaves = chaves';
        end
        
        
        function filter_dataset = remover_repetidos(data, k, n)
        
            filter_dataset = {};
            bloom_filter = zeros(1, n);
        
            for i = 1:size(data, 1)
                
                value = data(i, :);
                key = cat(2, value{1, 1}, ' ', value{1, 2}, ' ', value{1, 3});
                
                if BloomFilter.bloom_filter_maybe_in(bloom_filter, key, k) == 0
                    bloom_filter = BloomFilter.bloom_filter_insert(bloom_filter, key, k);
                    filter_dataset = [filter_dataset; value];
                end
        
            end
        end
        
        
        function filter_dataset = remover_repetidos_playlist(filter, dataset, k)
        
            filter_dataset = {};
            chaves_dataset = BloomFilter.dataset_init(dataset);
        
            for i = 1:size(chaves_dataset, 2)
                
                key = chaves_dataset{i};
                
                if BloomFilter.bloom_filter_maybe_in(filter, key, k) == 0
                    filter_dataset = [filter_dataset; dataset(i, :)];
                else
                    disp(dataset(i, :))
                end
        
            end
        end
    end
end