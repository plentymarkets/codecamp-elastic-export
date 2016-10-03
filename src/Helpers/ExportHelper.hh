<?hh //strict

namespace CodeCampExport\Helpers;

use Plenty\Modules\Item\DataLayer\Models\Record;
use Plenty\Modules\Helper\Models\KeyValue;

class ExportHelper
{
    const int REMOVE_HTML_TAGS = 1;
    const int KEEP_HTML_TAGS = 0;

	/**
	 * Get the description fields by checking the format configuration.
	 * 
	 * @param KeyValue $settings
	 * @return mixed
	 */
	public function getDescriptionFields(KeyValue $settings):mixed
	{
		$fields = ['urlContent'];
        $fields[] = ($settings->get('nameId')) ? 'name' . $settings->get('nameId') : 'name1';

        if($settings->get('descriptionType') == 'itemShortDescription'
            || $settings->get('previewTextType') == 'itemShortDescription')
        {
            $fields[] = 'shortDescription';
        }

        if($settings->get('descriptionType') == 'itemDescription'
            || $settings->get('descriptionType') == 'itemDescriptionAndTechnicalData'
            || $settings->get('previewTextType') == 'itemDescription'
            || $settings->get('previewTextType') == 'itemDescriptionAndTechnicalData')
        {
            $fields[] = 'description';
        }

        if($settings->get('descriptionType') == 'technicalData'
            || $settings->get('descriptionType') == 'itemDescriptionAndTechnicalData'
            || $settings->get('previewTextType') == 'technicalData'
            || $settings->get('previewTextType') == 'itemDescriptionAndTechnicalData')
        {
            $fields[] = 'technicalData';
        }

        return $fields;
	}

	/**
     * Get name based on the selected options.
     *
     * @param  Record    $item
     * @param  KeyValue  $settings     
     * @return string
     */
    public function getName(Record $item, KeyValue $settings):string
	{
		switch($settings->get('nameId'))
		{
			case 3:
				$name = $item->itemDescription->name3;
                break;

			case 2:
				$name = $item->itemDescription->name2;
                break;

			case 1:
			default:
				$name = $item->itemDescription->name1;
                break;
		}

        return substr($name, 0, $settings->get('nameMaxLength') ?: 60);
    }

    /**
     * Get description.
     *
     * @param  Record        $item
     * @param  KeyValue      $settings     
     * @return string
     */
    public function getDescription(Record $item, KeyValue $settings):string
    {
        switch($settings->get('descriptionType'))
        {
            case 'itemShortDescription':
                $description = $item->itemDescription->shortDescription;
                break;

            case 'technicalData':
                $description = $item->itemDescription->technicalData;
                break;

            case 'itemDescriptionAndTechnicalData':
                $description = $item->itemDescription->description . ' ' . $item->itemDescription->technicalData;
                break;

            case 'itemDescription':
            default:
                $description = $item->itemDescription->description;
                break;
        }
        
        if($settings->get('descriptionRemoveHtmlTags') == self::REMOVE_HTML_TAGS)
        {
            $description = strip_tags($description, str_replace([',', ' '], '', $settings->get('previewTextAllowHtmlTags')));
        }
 
        return substr($description, 0, $settings->get('descriptionMaxLength') ?: 1000);
    }
}