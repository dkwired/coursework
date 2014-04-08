
COPY users ( user_id , password , first_name , last_name , e_mail , street1 , state , country , zipcode , balance)
FROM '/tmp/kleind/dataset/users.data' 
WITH DELIMITER ';';
 
COPY super_user ( super_user_id )
FROM '/tmp/kleind/dataset/superusers.data' 
WITH DELIMITER ';';

COPY follow (user_id_to , user_id_from , follow_time)
FROM '/tmp/kleind/dataset/followers.data' 
WITH DELIMITER ';';

COPY video ( video_id , title , year, online_price, dvd_price)
FROM '/tmp/kleind/dataset/video.data' 
WITH DELIMITER ';';

COPY genre ( genre_id , genre_name )
FROM '/tmp/kleind/dataset/genre.data' 
WITH DELIMITER ';';

COPY categorize ( video_id , genre_id )
FROM '/tmp/kleind/dataset/categorize.data' 
WITH DELIMITER ';';

COPY director ( director_id , first_name , last_name )
FROM '/tmp/kleind/dataset/director.data' 
WITH DELIMITER ';';

COPY star ( star_id , first_name , last_name )
FROM '/tmp/kleind/dataset/stars.data' 
WITH DELIMITER ';';

COPY author ( author_id , first_name , last_name )
FROM '/tmp/kleind/dataset/authors.data' 
WITH DELIMITER ';';

COPY directed ( video_id , director_id)
FROM '/tmp/kleind/dataset/directed.data' 
WITH DELIMITER ';';

COPY played ( video_id, star_id)
FROM '/tmp/kleind/dataset/played.data' 
WITH DELIMITER ';';

COPY written ( video_id , author_id )
FROM '/tmp/kleind/dataset/written.data' 
WITH DELIMITER ';';

