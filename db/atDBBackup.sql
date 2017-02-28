/* Disable foreign keys */
PRAGMA foreign_keys = 'off';

/* Begin transaction */
BEGIN;

/* Database properties */
PRAGMA auto_vacuum = 0;
PRAGMA encoding = 'UTF-8';
PRAGMA page_size = 1024;

/* Drop table [abImage] */
DROP TABLE IF EXISTS [main].[abImage];

/* Table structure [abImage] */
CREATE TABLE [main].[abImage](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, 
    [file_name] VARCHAR(512) NOT NULL UNIQUE, 
    [date] DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP);

/* Drop table [abImage_note] */
DROP TABLE IF EXISTS [main].[abImage_note];

/* Table structure [abImage_note] */
CREATE TABLE [main].[abImage_note](
    [image_id] INTEGER NOT NULL REFERENCES abImage([id]) ON DELETE CASCADE, 
    [note_ID] INTEGER REFERENCES note([id]) ON DELETE CASCADE);

/* Drop table [antibody] */
DROP TABLE IF EXISTS [main].[antibody];

/* Table structure [antibody] */
CREATE TABLE [main].[antibody](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [antibodytype] VARCHAR, 
    [manufacturer] VARCHAR(200), 
    [lot_number] VARCHAR(200), 
    [location] VARCHAR(200), 
    [received] DATETIME, 
    [notes] VARCHAR(512), 
    [storage_temp] INTEGER, 
    [used] BOOLEAN, 
    [tube_label] VARCHAR(512), 
    [hostspecies_id] INTEGER REFERENCES species([id]), 
    [protein_name] VARCHAR(200), 
    [protein_asc_id] VARCHAR(200), 
    [targetspecies_id] INTEGER REFERENCES species([id]), 
    [fluorophore_id] INTEGER REFERENCES fluorophore([id]), 
    CHECK([used] IN (0, 1)));

/* Drop table [block] */
DROP TABLE IF EXISTS [main].[block];

/* Table structure [block] */
CREATE TABLE [main].[block](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT, 
    [created] DATETIME DEFAULT (DATETIME ('now', 'localtime')), 
    [created_by] INTEGER REFERENCES user([id]), 
    [modified] DATETIME DEFAULT (DATETIME ('now', 'localtime')), 
    [status] INTEGER DEFAULT 0, 
    [label] VARCHAR(200) DEFAULT none);

/* Drop table [block_note] */
DROP TABLE IF EXISTS [main].[block_note];

/* Table structure [block_note] */
CREATE TABLE [main].[block_note](
    [block_id] INTEGER REFERENCES block([id]) ON DELETE CASCADE ON UPDATE CASCADE, 
    [note_id] INTEGER REFERENCES note([id]) ON DELETE CASCADE ON UPDATE CASCADE);

/* Drop table [channelsetting] */
DROP TABLE IF EXISTS [main].[channelsetting];

/* Table structure [channelsetting] */
CREATE TABLE [main].[channelsetting](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [microscoperound_id] INTEGER REFERENCES microscoperound([id]), 
    [stain_id] INTEGER REFERENCES stain([id]), 
    [exposure_time] INTEGER, 
    [z_offset] FLOAT);

/* Drop table [fluorophore] */
DROP TABLE IF EXISTS [main].[fluorophore];

/* Table structure [fluorophore] */
CREATE TABLE [main].[fluorophore](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT, 
    [status] INTEGER, 
    [created] DATETIME DEFAULT (DATETIME ('now')), 
    [modified] DATETIME DEFAULT (DATETIME ('now')), 
    [name] VARCHAR(200), 
    [excitation_max] INTEGER, 
    [emission_max] INTEGER);

/* Drop table [frame] */
DROP TABLE IF EXISTS [main].[frame];

/* Table structure [frame] */
CREATE TABLE [main].[frame](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [order] INTEGER, 
    [sectionimageplan_id] INTEGER REFERENCES sectionimageplan([id]), 
    [pos_x] FLOAT, 
    [pos_y] FLOAT, 
    [pos_i] INTEGER, 
    [pos_j] INTEGER);

/* Drop table [image] */
DROP TABLE IF EXISTS [main].[image];

/* Table structure [image] */
CREATE TABLE [main].[image](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [imagepath] VARCHAR(100), 
    [channel_setting_id] INTEGER REFERENCES channelsetting([id]), 
    [z_order] INTEGER, 
    [z_pos] FLOAT, 
    [frame_id] INTEGER REFERENCES frame([id]));

/* Drop table [imageStainSession] */
DROP TABLE IF EXISTS [main].[imageStainSession];

/* Table structure [imageStainSession] */
CREATE TABLE [main].[imageStainSession](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT, 
    [name] VARCHAR, 
    [immunoProtocol] INTEGER REFERENCES immunoprotocol([id]));

/* Drop table [immunoprotocol] */
DROP TABLE IF EXISTS [main].[immunoprotocol];

/* Table structure [immunoprotocol] */
CREATE TABLE [main].[immunoprotocol](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT, 
    [status] INTEGER, 
    [created] DATETIME DEFAULT (DATETIME ('now')), 
    [modified] DATETIME DEFAULT (DATETIME ('now')), 
    [name] VARCHAR(100), 
    [notes] VARCHAR(1024));

/* Drop table [lineartransform] */
DROP TABLE IF EXISTS [main].[lineartransform];

/* Table structure [lineartransform] */
CREATE TABLE [main].[lineartransform](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [microscoperound_id] INTEGER REFERENCES microscoperound([id]), 
    [ribbon_id] INTEGER REFERENCES ribbon([id]), 
    [a00] FLOAT, 
    [a10] FLOAT, 
    [a11] FLOAT, 
    [a12] FLOAT, 
    [b0] FLOAT, 
    [b1] FLOAT);

/* Drop table [microscoperound] */
DROP TABLE IF EXISTS [main].[microscoperound];

/* Table structure [microscoperound] */
CREATE TABLE [main].[microscoperound](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [round_id] INTEGER REFERENCES round([id]));

/* Drop table [note] */
DROP TABLE IF EXISTS [main].[note];

/* Table structure [note] */
CREATE TABLE [main].[note](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, 
    [note] TEXT, 
    [created_on] DATETIME DEFAULT (DATETIME ('now', 'localtime')), 
    [created_by] VARCHAR(256) REFERENCES user([id]));

/* Drop table [ribbon] */
DROP TABLE IF EXISTS [main].[ribbon];

/* Table structure [ribbon] */
CREATE TABLE [main].[ribbon](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [block_id] INTEGER REFERENCES block([id]) ON DELETE CASCADE, 
    [status] INTEGER DEFAULT 0, 
    [created] DATETIME DEFAULT (DATETIME ('now', 'localtime')), 
    [modified] DATETIME, 
    [cutting_order] INTEGER NOT NULL DEFAULT (- 1), 
    [notes] TEXT);

/* Drop table [round] */
DROP TABLE IF EXISTS [main].[round];

/* Table structure [round] */
CREATE TABLE [main].[round](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME);

/* Drop table [round_ribbon] */
DROP TABLE IF EXISTS [main].[round_ribbon];

/* Table structure [round_ribbon] */
CREATE TABLE [main].[round_ribbon](
    [round_id] INTEGER REFERENCES round([id]), 
    [ribbon_id] INTEGER REFERENCES ribbon([id]));

/* Drop table [section] */
DROP TABLE IF EXISTS [main].[section];

/* Table structure [section] */
CREATE TABLE [main].[section](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [ribbon_id] INTEGER REFERENCES ribbon([id]), 
    [order] INTEGER, 
    [pos_x] FLOAT, 
    [pos_y] FLOAT, 
    [angle] FLOAT, 
    [notes] VARCHAR(512));

/* Drop table [sectionimageplan] */
DROP TABLE IF EXISTS [main].[sectionimageplan];

/* Table structure [sectionimageplan] */
CREATE TABLE [main].[sectionimageplan](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [volume_id] INTEGER REFERENCES volume([id]), 
    [section_id] INTEGER REFERENCES section([id]), 
    [mx] INTEGER, 
    [my] INTEGER, 
    [pos_x] FLOAT, 
    [pos_y] FLOAT, 
    [overlap] FLOAT);

/* Drop table [species] */
DROP TABLE IF EXISTS [main].[species];

/* Table structure [species] */
CREATE TABLE [main].[species](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [name] VARCHAR(200));

/* Drop table [stain] */
DROP TABLE IF EXISTS [main].[stain];

/* Table structure [stain] */
CREATE TABLE [main].[stain](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [staintype] VARCHAR, 
    [fluorophore_id] INTEGER REFERENCES fluorophore([id]), 
    [primary_antibody_id] INTEGER REFERENCES antibody([id]), 
    [primary_dilution] INTEGER, 
    [secondary_antibody_id] INTEGER REFERENCES antibody([id]), 
    [secondary_dilution] INTEGER);

/* Drop table [stainround] */
DROP TABLE IF EXISTS [main].[stainround];

/* Table structure [stainround] */
CREATE TABLE [main].[stainround](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [round_id] INTEGER REFERENCES round([id]), 
    [immunoprotocol_id] INTEGER REFERENCES immunoprotocol([id]));

/* Drop table [stain_stainround] */
DROP TABLE IF EXISTS [main].[stain_stainround];

/* Table structure [stain_stainround] */
CREATE TABLE [main].[stain_stainround](
    [stainround_id] INTEGER REFERENCES stainround([id]), 
    [stain_id] INTEGER REFERENCES stain([id]));

/* Drop table [user] */
DROP TABLE IF EXISTS [main].[user];

/* Table structure [user] */
CREATE TABLE [main].[user](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [user_name] TEXT UNIQUE DEFAULT "New User", 
    [created] DATETIME DEFAULT (DATETIME ('now')));

/* Drop table [volume] */
DROP TABLE IF EXISTS [main].[volume];

/* Table structure [volume] */
CREATE TABLE [main].[volume](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
    [status] INTEGER, 
    [created] DATETIME, 
    [modified] DATETIME, 
    [name] VARCHAR(50), 
    [notes] VARCHAR(512));

/* Drop table [volumn_ribbon] */
DROP TABLE IF EXISTS [main].[volumn_ribbon];

/* Table structure [volumn_ribbon] */
CREATE TABLE [main].[volumn_ribbon](
    [volume_id] INTEGER REFERENCES volume([id]), 
    [ribbon_id] INTEGER REFERENCES ribbon([id]));

/* Table data [abImage] Record count: 3 */
INSERT INTO [abImage]([rowid], [id], [file_name], [date]) VALUES(38, 38, '19.jpg', '2016-09-30 21:38:40.000');
INSERT INTO [abImage]([rowid], [id], [file_name], [date]) VALUES(39, 39, '20.jpg', '2016-09-30 21:38:50.000');
INSERT INTO [abImage]([rowid], [id], [file_name], [date]) VALUES(40, 40, '21.jpg', '2016-10-01 00:22:19.000');

/* Table data [abImage_note] Record count: 2 */
INSERT INTO [abImage_note]([rowid], [image_id], [note_ID]) VALUES(1, 38, 158);
INSERT INTO [abImage_note]([rowid], [image_id], [note_ID]) VALUES(2, 40, 159);

/* Table data [antibody] Record count: 0 */

/* Table data [block] Record count: 3 */
INSERT INTO [block]([rowid], [id], [created], [created_by], [modified], [status], [label]) VALUES(113, 113, '2016-06-20 15:55:48.000', 20, '2016-06-20 15:55:48.000', 0, 'none');
INSERT INTO [block]([rowid], [id], [created], [created_by], [modified], [status], [label]) VALUES(114, 114, '2016-09-21 15:17:17.000', 17, '2016-09-21 15:17:17.000', 0, 'none');
INSERT INTO [block]([rowid], [id], [created], [created_by], [modified], [status], [label]) VALUES(124, 124, '2016-09-21 17:11:18.000', 17, '2016-09-21 17:11:18.000', 0, 'none');

/* Table data [block_note] Record count: 0 */

/* Table data [channelsetting] Record count: 0 */

/* Table data [fluorophore] Record count: 5 */
INSERT INTO [fluorophore]([rowid], [id], [status], [created], [modified], [name], [excitation_max], [emission_max]) VALUES(1, 1, null, '2016-06-20 19:12:02.000', '2016-06-20 19:12:02.000', 'Quasar', null, null);
INSERT INTO [fluorophore]([rowid], [id], [status], [created], [modified], [name], [excitation_max], [emission_max]) VALUES(2, 2, null, '2016-06-20 19:12:17.000', '2016-06-20 19:12:17.000', 'Fluoro 1', null, null);
INSERT INTO [fluorophore]([rowid], [id], [status], [created], [modified], [name], [excitation_max], [emission_max]) VALUES(3, 3, null, '2016-06-20 19:12:25.000', '2016-06-20 19:12:25.000', 'Fluoro 2', null, null);
INSERT INTO [fluorophore]([rowid], [id], [status], [created], [modified], [name], [excitation_max], [emission_max]) VALUES(4, 4, null, '2016-06-20 19:12:38.000', '2016-06-20 19:12:38.000', 'Fluoro 3', null, null);
INSERT INTO [fluorophore]([rowid], [id], [status], [created], [modified], [name], [excitation_max], [emission_max]) VALUES(5, 5, null, '2016-06-20 19:12:47.000', '2016-06-20 19:12:47.000', 'Fluoro 4', null, null);

/* Table data [frame] Record count: 0 */

/* Table data [image] Record count: 0 */

/* Table data [imageStainSession] Record count: 2 */
INSERT INTO [imageStainSession]([rowid], [id], [name], [immunoProtocol]) VALUES(1, 1, 'My First Session', null);
INSERT INTO [imageStainSession]([rowid], [id], [name], [immunoProtocol]) VALUES(2, 2, 'Second', null);

/* Table data [immunoprotocol] Record count: 3 */
INSERT INTO [immunoprotocol]([rowid], [id], [status], [created], [modified], [name], [notes]) VALUES(1, 1, null, '2016-06-20 21:23:48.000', '2016-06-20 21:23:48.000', 'Immuno Protocol 1', null);
INSERT INTO [immunoprotocol]([rowid], [id], [status], [created], [modified], [name], [notes]) VALUES(2, 2, null, '2016-06-20 21:24:07.000', '2016-06-20 21:24:07.000', 'Immuno Protocol 2', null);
INSERT INTO [immunoprotocol]([rowid], [id], [status], [created], [modified], [name], [notes]) VALUES(3, 3, null, '2016-06-20 21:24:17.000', '2016-06-20 21:24:17.000', 'Immuno Protocol 3', null);

/* Table data [lineartransform] Record count: 0 */

/* Table data [microscoperound] Record count: 0 */

/* Table data [note] Record count: 2 */
INSERT INTO [note]([rowid], [id], [note], [created_on], [created_by]) VALUES(158, 158, 'New note.. asd fad', '2016-10-03 16:18:31.000', '17');
INSERT INTO [note]([rowid], [id], [note], [created_on], [created_by]) VALUES(159, 159, 'New note.. rg ', '2016-10-03 17:14:51.000', '17');

/* Table data [ribbon] Record count: 7 */
INSERT INTO [ribbon]([rowid], [id], [block_id], [status], [created], [modified], [cutting_order], [notes]) VALUES(147, 147, 113, 0, '2016-06-20 15:55:56.000', null, -1, null);
INSERT INTO [ribbon]([rowid], [id], [block_id], [status], [created], [modified], [cutting_order], [notes]) VALUES(148, 148, 113, 0, '2016-06-20 15:55:57.000', null, -1, null);
INSERT INTO [ribbon]([rowid], [id], [block_id], [status], [created], [modified], [cutting_order], [notes]) VALUES(149, 149, 113, 0, '2016-06-20 15:55:57.000', null, -1, null);
INSERT INTO [ribbon]([rowid], [id], [block_id], [status], [created], [modified], [cutting_order], [notes]) VALUES(150, 150, 113, 0, '2016-06-20 15:55:57.000', null, -1, null);
INSERT INTO [ribbon]([rowid], [id], [block_id], [status], [created], [modified], [cutting_order], [notes]) VALUES(151, 151, 113, 0, '2016-06-20 15:55:57.000', null, -1, null);
INSERT INTO [ribbon]([rowid], [id], [block_id], [status], [created], [modified], [cutting_order], [notes]) VALUES(152, 152, 113, 0, '2016-06-20 15:56:10.000', null, -1, null);
INSERT INTO [ribbon]([rowid], [id], [block_id], [status], [created], [modified], [cutting_order], [notes]) VALUES(153, 153, 113, 0, '2016-06-20 15:56:22.000', null, -1, null);

/* Table data [round] Record count: 0 */

/* Table data [round_ribbon] Record count: 0 */

/* Table data [section] Record count: 0 */

/* Table data [sectionimageplan] Record count: 0 */

/* Table data [species] Record count: 8 */
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(1, 1, null, null, null, 'species 1');
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(2, 2, null, null, null, 'species 2');
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(3, 3, null, null, null, 'species 3');
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(4, 4, null, null, null, 'donkey');
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(5, 5, null, null, null, 'ape');
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(6, 6, null, null, null, 'human');
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(7, 7, null, null, null, 'parrot');
INSERT INTO [species]([rowid], [id], [status], [created], [modified], [name]) VALUES(8, 8, null, null, null, 'pidgeon');

/* Table data [stain] Record count: 0 */

/* Table data [stainround] Record count: 0 */

/* Table data [stain_stainround] Record count: 0 */

/* Table data [user] Record count: 3 */
INSERT INTO [user]([rowid], [id], [user_name], [created]) VALUES(17, 17, 'Test2', '2016-06-17 16:40:59.000');
INSERT INTO [user]([rowid], [id], [user_name], [created]) VALUES(20, 20, 'Totte', '2016-06-17 20:47:41.000');
INSERT INTO [user]([rowid], [id], [user_name], [created]) VALUES(27, 27, 'Bla', '2016-09-22 00:21:16.000');

/* Table data [volume] Record count: 0 */

/* Table data [volumn_ribbon] Record count: 0 */

/* Commit transaction */
COMMIT;

/* Enable foreign keys */
PRAGMA foreign_keys = 'on';
