/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#ifndef QFB_QFB_H
#define QFB_QFB_H

/**
 * @file qfb.h
 * @short Global enumerations used in qfb
 */

namespace QFB
{

/**
 * @brief Enumeration describing the properties that a Facebook entry can have
 */
enum Property {
    /**
     * @short The entry's Facebook ID
     */
    IdProperty,
    ObjectTypeProperty,
    /**
     * @short The last time the entry was updated.
     *
     * If it is related to an user, changes to the languages, link, timezone, verified,
     * interested_in, favorite_athletes, favorite_teams, and video_upload_limits are not
     * reflected in this value.
     */
    UpdatedTimeProperty,
    /**
     * @short The entry's name
     *
     * It can be the name of an user, or the name of a link in a
     * post.
     */
    NameProperty,
    /**
     * @short The user's first name
     */
    FirstNameProperty,
    /**
     * @short The user's middle name
     */
    MiddleNameProperty,
    /**
     * @short The user's last name
     */
    LastNameProperty,
    /**
     * @short The user's gender: female or male
     * @todo define an enumeration for that.
     */
    GenderProperty,
    /**
     * @short The user's locale
     *
     * The locale is provided as an ISO Language Code and ISO Country Code.
     */
    LocaleProperty,
    /**
     * @short The user's languages
     */
    LanguagesProperty,
    /**
     * @short A link
     *
     * For an user it is the URL of the profile for the user on Facebook,
     * for a post, it is the link attached to this post.
     */
    LinkProperty,
    /**
     * @short The user's Facebook username
     */
    UsernameProperty,
    /**
     * @short The user's timezone offset from UTC
     *
     * Available only for the current user.
     */
    TimezoneProperty,
    /**
     * @short The user's biography
     */
    BioProperty,
    /**
     * @short The user's birthday
     *
     * Requires \e user_birthday or \e friends_birthday.
     */
    BirthdayProperty,
    /**
     * @short The user's cover photo
     *
     * (must be explicitly requested using fields=cover parameter)
     */
    CoverProperty,
    /**
     * @short The user's currency settings
     *
     * (must be explicitly requested using a fields=currency URL parameter)
     */
    Currency,
    /**
     * @short A list of the user's devices beyond desktop
     * @todo comment
     */
    DevicesProperty,
    /**
     * A list of the user's education history
     */
    EducationProperty,
    /**
     * @short The proxied or contact email address granted by the user
     *
     * Requires \e email.
     */
    EmailProperty,
    /**
     * @short The user's hometown
     *
     * Requires \e user_hometown or \e friends_hometown.
     */
    HometownProperty,
    /**
     * @short The genders the user is interested in
     *
     * Requires \e user_relationship_details or \e friends_relationship_details.
     */
    InterestedInProperty,
    /**
     * @short The user's current city
     *
     * Requires \e user_location or \e friends_location.
     */
    LocationProperty,
    /**
     * @short The user's political view
     *
     * Requires \e user_religion_politics or \e friends_religion_politics
     */
    PoliticalProperty,
    /**
     * @short The payment price-points available for that user
     */
    PaymentPricepointsProperty,
    /**
     * @short A picture
     *
     * For an user, it is the URL of the user's profile pic, and is only
     * returned if you explicitly specify a 'fields=picture' param.
     *
     * For a post, it is, if available, a link to the picture included
     * with the post.
     */
    PictureProperty,
    /**
     * @short The user's favorite quotes
     *
     * Requires \e user_about_me or \e friends_about_me.
     */
    QuotesProperty,
    /**
     * @short The user's relationship status.
     * It can be Single, In a relationship, Engaged, Married,
     * It's complicated, In an open relationship, Widowed,
     * Separated, Divorced, In a civil union,
     * In a domestic partnership.
     *
     * Requires \e user_relationships or \e friends_relationships
     */
    RelationshipStatusProperty,
    /**
     * @short The user's religion
     *
     * Requires \e user_religion_politics or \e friends_religion_politics.
     */
    ReligionProperty,
    /**
     * @short Information about security settings enabled on the user's account
     *
     * It must be explicitly requested using a fields=security_settings URL parameter.
     */
    SecuritySettingsProperty,
    /**
     * @short The user's significant other
     *
     * Requires \e user_relationships or \e friends_relationships.
     */
    SignificantOtherProperty,
    /**
     * @short The size of the video file and the length of the video that a user can upload.
     *
     * It is only returned if specifically requested via the fields URL parameter.
     */
    VideoUploadLimitsProperty,
    /**
     * @short The URL of the user's personal website
     *
     * Requires \e user_website or \e friends_website.
     */
    WebsiteProperty,
    /**
     * @short A list of the user's work history
     *
     * Requires \e user_work_history or \e friends_work_history.
     */
    WorkProperty,
    /**
     * @short The user who posted the message
     */
    FromProperty,
    /**
     * @short Profiles mentioned or targeted in this post
     */
    ToProperty,
    /**
     * @short The message
     */
    MessageProperty,
    /**
     * @short Objects tagged in the message (Users, Pages, etc)
     */
    MessageTagsProperty,
    /**
     * @short The caption of the link
     *
     * The caption appears beneath the link name.
     */
    CaptionProperty,
    /**
     * @short A description of the link
     *
     * The description appears beneath the link caption.
     */
    DescriptionProperty,
    /**
     * @short A source
     *
     * For a post, it is the URL to a Flash movie or video file to be
     * embedded within the post. For a cover, it is the URL of the image.
     */
    SourceProperty,
    /**
     * @short A list of properties for an uploaded video
     *
     * It contains, for example, the length of the video.
     */
    PropertiesProperty,
    /**
     * @short A link to an icon representing the type of this post
     */
    IconProperty,
    /**
     * @short A list of available actions on the post
     *
     * It includes for example commenting, liking, and an optional
     * app-specified action.
     */
    ActionsProperty,
    /**
     * @short The privacy settings of the post
     */
    PrivacyProperty,
    /**
     * @short A string indicating the type for this post
     *
     * It can be a link, photo, video, etc.
     */
    TypeProperty,
    /**
     * @short Likes for this post
     */
    LikesProperty,
    /**
     * @short Location associated with a post, if any
     */
    PlaceProperty,
    /**
     * @short Text of stories not intentionally generated by users
     *
     * It can be, for example, a story generated when two users become friends; you must have the
     * "Include recent activity stories" migration enabled in your app to retrieve these stories.
     */
    StoryProperty,
    /**
     * @short Objects (Users, Pages, etc) tagged in a non-intentional story
     *
     * You must have the "Include recent activity stories" migration enabled
     * in your app to retrieve these tags.
     */
    StoryTagsProperty,
    /**
     * @short Objects (Users, Pages, etc) tagged as being with the publisher of the post
     *
     * It is, for example, the list of "Who are you with?" on Facebook.
     */
    WithTagsProperty,
    /**
     * @short Comments for this post
     */
    CommentsProperty,
    /**
     * @short The Facebook object id for an uploaded photo or video in a post
     */
    ObjectIdProperty,
    /**
     * @short Information about the application this post came from
     */
    ApplicationProperty,
    /**
     * @short The time the post was initially published
     */
    CreatedTimeProperty,
    /**
     * @short Whether to include posts that have been set to Hidden from Timeline
     */
    IncludeHiddenProperty,
    /**
     * @short The vertical offset that is displayed for the cover
     */
    OffsetYProperty
};

enum RequestType {
    NoRequest,
    TypeRequest,
    UserRequest,
    PictureRequest

};

void qfbRegisterMetatype();

}

#endif // QFB_QFB_H
