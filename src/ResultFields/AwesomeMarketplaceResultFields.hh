<?hh //strict
namespace CodeCampExport\ResultFields;

use Plenty\Modules\DataExchange\Contracts\ResultFields;
use Plenty\Modules\DataExchange\Models\FormatSetting;
use Plenty\Modules\Helper\Services\ArrayHelper;

use CodeCampExport\Helpers\ExportHelper;

class AwesomeMarketplaceResultFields extends ResultFields
{
    /*
	 * ArrayHelper $arrayHelper
	 */
	private ArrayHelper $arrayHelper;

    /**
     * ExportHelper $exportHelper
     */
    private ExportHelper $exportHelper;

    /**     
     * @param ArrayHelper $arrayHelper
     * @param ExportHelper $exportHelper
     */
    public function __construct(ArrayHelper $arrayHelper, ExportHelper $exportHelper)
    {
		$this->arrayHelper = $arrayHelper;
        $this->exportHelper = $exportHelper;
    }

    /**
     * Generate result fields.
     * @param  array<FormatSetting> $formatSettings = []
     * @return array<string, mixed>
     */
    public function generateResultFields(array<FormatSetting> $formatSettings = []):array<string, mixed>
    {
        $settings = $this->arrayHelper->buildMapFromObjectList($formatSettings, 'key', 'value');        

        return [
            'itemBase'=> [
                'id',                
            ],

            'itemDescription' => [
                'params' => [
                    'language' => $settings->get('lang') ? $settings->get('lang') : 'de',
                ],
                'fields' => $this->exportHelper->getDescriptionFields($settings),
            ],            
            
            'variationRetailPrice' => [
                'price',
            ],            

            'variationStock' => [
                'params' => [
                    'type' => 'virtual'
                ],
                'fields' => [
                    'stockNet'
                ]
            ],            
        ];
    }
}
