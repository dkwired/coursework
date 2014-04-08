
DELETE FROM users WHERE *;
COPY users ( user_id , password , first_name , last_name , e_mail , street1 , state , country , zipcode , balance)
FROM '../../phase3/dataset/users.data' 
WITH DELIMITER ';';

DELETE FROM super_user WHERE *;
COPY super_user ( super_user_id )
FROM '../../phase3/dataset/superusers.data' 
WITH DELIMITER ';';

DELETE FROM follow WHERE *;
COPY follow (user_id_to , user_id_from , follow_time)
FROM '../../phase3/dataset/followers.data' 
WITH DELIMITER ';';

DELETE FROM video;
COPY video ( video_id , title , year, online_price, dvd_price)
FROM '../../phase3/dataset/video.data' 
WITH DELIMITER ';';

DELETE FROM genre;
COPY genre ( genre_id , genre_name )
FROM '../../phase3/dataset/genre.data' 
WITH DELIMITER ';';

DELETE FROM categorize;
COPY categorize ( video_id , genre_id )
FROM '../../phase3/dataset/categorize.data' 
WITH DELIMITER ';';

DELETE FROM director;
COPY director ( director_id , first_name , last_name )
FROM '../../phase3/dataset/director.data' 
WITH DELIMITER ';';

DELETE FROM star;
COPY star ( star_id , first_name , last_name )
FROM '../../phase3/dataset/stars.data' 
WITH DELIMITER ';';

DELETE FROM author;
COPY author ( author_id , first_name , last_name )
FROM '../../phase3/dataset/authors.data' 
WITH DELIMITER ';';

DELETE FROM directed;
COPY directed ( video_id , director_id)
FROM '../../phase3/dataset/directed.data' 
WITH DELIMITER ';';

DELETE FROM played;
COPY played ( video_id, star_id)
FROM '../../phase3/dataset/played.data' 
WITH DELIMITER ';';

DELETE FROM written;
COPY written ( video_id , author_id )
FROM '../../phase3/dataset/written.data' 
WITH DELIMITER ';';
